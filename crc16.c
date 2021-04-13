unsigned short crc16(unsigned short crc, unsigned char *p, int len)
{
          while (len--)
               crc = (crc >> 8) ^ crctab[(crc ^ *p++) & 0xff];
          return crc;
}
