"""Unit tests for units module."""

import math

from skydelsdx import units


def test_toRadian():
    assert math.isclose(units.toRadian(180), units.PI)
