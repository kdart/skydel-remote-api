"""Base Skydel client."""

import socket
import struct
import sys
import time


class CLientError(OSError):
  pass


class Client:

  def __init__(self):
    self._address = None
    self._sock = None

  def __del__(self):
    self.close()

  def close(self):
    if self._sock is not None:
      self._sock.close()
      self._sock = None

  def connect(self, hostname, port=4820):
    if self._sock is not None:
      return
    for addrfamily, addrtype, _, _, addr in socket.getaddrinfo(
        hostname, port, family=socket.AF_UNSPEC, type=socket.SOCK_STREAM
    ):
      sock = socket.socket(addrfamily, addrtype)
      sock.connect(addr)
      self._sock = sock
      self._address = addr
      break

  @property
  def address(self):
    return self._address

  @property
  def port(self):
    return self._address[1] if self._address is not None else None

  @property
  def server_address(self):
    return self._address[0] if self._address is not None else None

  @property
  def sock(self):
    return self._sock

  def settimeout(self, time):
    if self._sock is not None:
      self._sock.settimeout(time)

  def _getPacket(self, size):
    packet = self.sock.recv(size)
    while len(packet) != size:
      chunk = self.sock.recv(size - len(packet))
      if len(chunk) == 0:
        raise ClientError('Server closed connection.')
      packet = packet + chunk
    return packet

  def _msgId2Packet(self, msgId):
    return struct.pack('<B', msgId)

  def _dynamicType2Packet(self, dynamicType):
    return struct.pack('<B', dynamicType)

  def _ecef2Packet(self, triplet):
    return struct.pack('<ddd', triplet.x, triplet.y, triplet.z)

  def _angle2Packet(self, triplet):
    return struct.pack('<ddd', triplet.yaw, triplet.pitch, triplet.roll)

  def _getPacketMsgId(self):
    return struct.unpack('<B', self._getPacket(1))[0]


class DgramClient(Client):

  def open(self, address):
    if self._sock is not None:
      return
    host_addr, port, *rest = address
    for addrfamily, addrtype, _, _, addr in socket.getaddrinfo(
        host_addr, port, family=socket.AF_UNSPEC, type=socket.SOCK_DGRAM
    ):
      sock = socket.socket(addrfamily, addrtype)
      self._sock = sock
      self._address = addr
      self._port = port
      break
