"""Tasks file used by the *invoke* command.

This simplifies some common development tasks.

Run these tasks with the `invoke` tool.
"""

import os
from pathlib import Path
import shutil
import sys

from invoke import Exit, run, task
import semver

PYTHONBIN = os.environ.get("PYTHONBIN", sys.executable)
# Put the path in quotes in case there is a space in it.
PYTHONBIN = f'"{PYTHONBIN}"'

PACKAGE_NAME = "Skydel SDX"
PACKAGE_BUILD = os.environ.get("SKYDEL_BUILD")


@task
def info(_):
    """Show information about the current Python and environment."""
    print(f"Python used: {PYTHONBIN}")
    venv = get_virtualenv()
    if venv:
        print("Virtual environment:", venv)


@task
def clean(ctx):
    """Clean out build and cache files."""
    ctx.run(r"find . -depth -type d -name __pycache__ -exec rm -rf {} \;")


@task
def flake8(ctx, pathname="skydelsdx"):
    """Run flake8 linter on the package."""
    ctx.run(f"{PYTHONBIN} -m flake8 {pathname}")


@task
def reformat(ctx, pathname="skydelsdx", check=False, changed=False, untracked=False):
    """Run yapf formatter on the specified file, or changed files.

    Recurse into subdirectory.
    """
    option = "-d" if check else "-i"
    if changed:
        files = get_modified_files(untracked)
        if files:
            ctx.run(f'{PYTHONBIN} -m yapf --style setup.cfg {option} {" ".join(files)}')
        else:
            print("No changed python files.")
    else:
        recurse = "--recursive" if os.path.isdir(pathname) else ""
        ctx.run(f"{PYTHONBIN} -m yapf --style setup.cfg {option} {recurse} {pathname}")


@task
def cleandist(_):
    """Clean out dist subdirectory."""
    if os.path.isdir("dist"):
        shutil.rmtree("dist", ignore_errors=True)
        os.mkdir("dist")
    if os.path.isdir("wheelhouse"):
        shutil.rmtree("wheelhouse", ignore_errors=True)


@task
def dev_requirements(ctx):
    """Install development requirements."""
    user = "" if os.environ.get("VIRTUAL_ENV") else "--user"
    ctx.run(
        f'{PYTHONBIN} -m pip install --index-url "{ctx.config.pypi.index}" '
        f"--upgrade {user} -r dev-requirements.txt",
        pty=True,
        hide=False,
    )


@task(pre=[dev_requirements])
def develop(ctx, uninstall=False):
    """Start developing in developer, or editable, mode."""
    user = "" if os.environ.get("VIRTUAL_ENV") else "--user"
    if uninstall:
        ctx.run(f"{PYTHONBIN} -m pip uninstall -y {PACKAGE_NAME}")
    else:
        ctx.run(f"{PYTHONBIN} -m pip --isolated install --index-url"
                f' "{ctx.config.pypi.index}" {user} --editable .')


@task
def test(ctx, testfile=None, ls=False):
    """Run unit tests. Use ls option to only list them."""
    if ls:
        ctx.run(f"{PYTHONBIN} -m pytest --collect-only -qq tests")
    elif testfile:
        ctx.run(f"{PYTHONBIN} -m pytest -s {testfile}", hide=False, pty=True)
    else:
        ctx.run(f"{PYTHONBIN} -m pytest tests", hide=False, pty=True)


@task
def tag(ctx, newtag=None, major=False, minor=False, patch=False):
    """Tag or bump release with a semver tag.

  Makes a signed tag if you're a signer.
  """
    latest = None
    if newtag is None:
        tags = get_tags()
        if not tags:
            latest = semver.VersionInfo(0, 0, 0)
        else:
            latest = tags[-1]
        if patch:
            nextver = latest.bump_patch()
        elif minor:
            nextver = latest.bump_minor()
        elif major:
            nextver = latest.bump_major()
        else:
            nextver = latest.bump_patch()
    else:
        if newtag.startswith("v"):
            newtag = newtag[1:]
        try:
            nextver = semver.parse_version_info(newtag)
        except ValueError:
            raise Exit("Invalid semver tag.", 2) from None

    if PACKAGE_BUILD is not None:
        nextver = nextver.replace(build=PACKAGE_BUILD)

    print(latest, "->", nextver)
    tagopt = "-s" if ctx.config.scm.signed else "-a"
    ctx.run(f'git tag {tagopt} -m "Update remote API to v{nextver}" v{nextver}')


@task
def tag_delete(ctx, tagname=None):
    """Delete a tag, both local and remote."""
    if tagname:
        ctx.run(f"git tag -d {tagname}")
        ctx.run(f"git push origin :refs/tags/{tagname}")


@task(cleandist)
def sdist(ctx):
    """Build source distribution."""
    ctx.run(f"{PYTHONBIN} setup.py sdist")


@task(sdist)
def bdist(ctx):
    """Build a standard wheel file, an installable format."""
    ctx.run(f"{PYTHONBIN} setup.py bdist_wheel")


@task(pre=[cleandist, sdist], aliases=["wheel"])
def build(ctx):
    """Build a standard wheel file, an installable format, with native arch."""
    ctx.run(f"{PYTHONBIN} -m build --no-isolation")


@task
def branch(ctx, name=None):
    """start a new branch, both local and remote tracking."""
    if name:
        ctx.run(f"git checkout -b {name}")
        ctx.run(f"git push -u origin {name}")
    else:
        ctx.run("git --no-pager branch")


@task
def branch_delete(ctx, name=None):
    """Delete local, remote and tracking branch by name."""
    if name:
        ctx.run(f"git branch -d {name}", warn=True)  # delete local branch
        ctx.run(f"git branch -d -r {name}", warn=True)  # delete local tracking info
        ctx.run(f"git push origin --delete {name}", warn=True)  # delete remote (origin) branch.
    else:
        print("Supply a branch name: --name <name>")


# Helper functions follow.
def get_virtualenv():
    """Get the virtual env name, or None."""
    venv = os.environ.get("VIRTUAL_ENV")
    if venv and os.path.isdir(venv):
        return venv
    return None


def get_tags():
    """Return list of semver compatible tags."""
    rv = run('git tag -l "v*"', hide="out")
    vilist = []
    for line in rv.stdout.split():
        try:
            vi = semver.parse_version_info(line[1:])
        except ValueError:
            pass
        else:
            vilist.append(vi)
    vilist.sort()
    return vilist


def resolve_path(base, p):
    p = Path(p)
    return str(base / p)


def find_git_base():
    """Find the base directory of this git repo.

    The git status output is always relative to this directory.
    """
    start = Path.cwd().resolve()
    while start:
        if (start / ".git").exists():
            return start
        start = start.parent
    raise Exit("Not able to find git repo base.")


def get_modified_files(untracked):
    """Find the list of modified and, optionally, untracked Python files.

    If `untracked` is True, also include untracked Python files.
    """
    filelist = []
    gitbase = find_git_base()
    gitout = run("git status --porcelain=1 -z", hide=True)
    for line in gitout.stdout.split("\0"):
        if line:
            if not line.endswith(".py"):
                continue
            if line[0:2] == " M":
                filelist.append(resolve_path(gitbase, line[3:]))
            if untracked and line[0:2] == "??":
                filelist.append(resolve_path(gitbase, line[3:]))
    return filelist
