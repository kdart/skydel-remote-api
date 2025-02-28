"""Common exception types."""


class CommandException(Exception):
  """Raised when a remote command returns failure."""

  def __init__(self, command_result, simulation_error_msg):
    msg = (
        command_result.getRelatedCommand().getName()
        + " failed: "
        + command_result.getMessage()
        + simulation_error_msg
    )
    super().__init__(msg)
    self._command_result = command_result
    self._simulation_error_msg = simulation_error_msg

  @property
  def command_result(self):
    return self._command_result

  @property
  def simulation_error_msg(self):
    return self._simulation_error_msg


class UsageError(ValueError):
  """Raised when a set of parameters is inconsistent."""


class OperationalError(RuntimeError):
  """Raised when something is not operating as expected."""
