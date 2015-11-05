#ifndef _FORMAT_H_
#define _FORMAT_H_

#include <string>
#include <sstream>
#include <iosfwd>
#include <iomanip>

class Format
{
public:
    //=============================================================================
    static void format(std::string& sF, const char* sformat, va_list marker)
    {
        char *s, ch=0;
        int n, i=0, m;
        long l;
        double d;
        std::string sf = sformat;
        std::stringstream ss;
        bool fill = false, first = true, point = false, comma = false;
        std::string width, precision;

        m = sf.length();

        while (i < m)
        {
            ch = sf.at(i);

            if (ch == '%')
            {
                bool format = true;

                while (i < m - 1 && format)
                {
                    i++;

                    ch = sf.at(i);

                    format = false;

                    if (width.length())
                    {
                        ss.width(atoi(width.c_str()));
                    }

                    if (fill)
                    {
                        ss.fill('0');
                    }

                    if (precision.length())
                    {
                        ss << std::fixed << std::setprecision(atoi(precision.c_str()));
                    }

                    if (point)
                    {
                        ss << std::fixed  << std::showpoint;
                    }

                    switch(ch)
                    {
                    case 's': { s = va_arg(marker, char*);  ss << s;         } break;
                    case 'c': { n = va_arg(marker, int);    ss << (char)n;   } break;
                    case 'd': { n = va_arg(marker, int);    ss << (int)n;    } break;
                    case 'l': { l = va_arg(marker, long);   ss << (long)l;   } break;
                    case 'f': { d = va_arg(marker, double); ss << (float)d;  } break;
                    case 'e': { d = va_arg(marker, double); ss << (double)d; } break;
                    case 'X':
                    case 'x':
                        {
                            if (++i<m)
                            {
                                ss << std::hex << std::setiosflags (std::ios_base::showbase);
                                if (ch == 'X') ss << std::setiosflags (std::ios_base::uppercase);
                                char ch2 = sf.at(i);
                                if (ch2 == 'c') { n = va_arg(marker, int);  ss << std::hex << (char)n; }
                                else if (ch2 == 'd') { n = va_arg(marker, int); ss << std::hex << (int)n; }
                                else if (ch2 == 'l') { l = va_arg(marker, long);    ss << std::hex << (long)l; }
                                else ss << '%' << ch << ch2;
                                ss << std::resetiosflags (std::ios_base::showbase | std::ios_base::uppercase) << std::dec;
                            }
                        } break;
                    case '%': { ss << '%'; } break;
                    default:
                        {
                            if (ch >= '0' && ch <= '9')
                            {
                                if (first && ch == '0')
                                {
                                    first = false;
                                    fill = true;
                                }
                                else if (point || comma)
                                {
                                    precision.push_back(ch);
                                }
                                else
                                {
                                    width.push_back(ch);
                                }

                                format = true;
                            }
                            else if (ch == '.')
                            {
                                point = true;

                                format = true;
                            }
                            else if (ch == ',')
                            {
                                comma = true; 

                                format = true;
                            }
                            else
                            {
                                ss << "%" << ch;
                            }
                        }
                    }
                }
            }
            else
            {
                ss << ch;
            }

            i++;
        }

        va_end(marker);

        sF = ss.str();
    };

    //=============================================================================
    static void sf(std::string& stgt, const char *sformat, ... )
    {
        va_list marker;
        va_start(marker, sformat);
        format(stgt, sformat, marker);
    }

    //=============================================================================
    static void sfa(std::string& stgt, const char *sformat, ... )
    {
        std::string sF = "";
        va_list marker;
        va_start(marker, sformat);
        format(sF, sformat, marker);
        stgt += sF;
    }

};

#endif // _FORMAT_H_
