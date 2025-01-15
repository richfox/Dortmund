#pragma once


enum Marking : unsigned char
{
   NOMARKED = 0x00,
   FIRST = 0x01,    //Bit 0
   SECOND = 0x02,   //Bit 1
   THIRD = 0x04,    //Bit 2
   FOURTH = 0x08,   //Bit 3
   FIFTH = 0x10,    //Bit 4
   SIXTH = 0x20     //Bit 5
};

static unsigned char g_mark = unsigned char(Marking::NOMARKED);

inline void set_mark(const Marking mark, const bool value)
{
   if (value)
      g_mark = g_mark | mark;
   else
      g_mark = g_mark & (~mark);
}

inline bool is_marked(const Marking mark)
{
   if ((g_mark & mark) == Marking::NOMARKED)
   {
      return false;
   }
   else
   {
      return true;
   }
}