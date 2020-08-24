#include "colorscale.hpp"

QColor ColorScale::getColorLabels() const
{
    return colorLabels;
}

void ColorScale::setColorLabels(const QColor &value)
{
    colorLabels = value;
}

ColorScale::ColorScale(QWidget* parent)
    : QWidget(parent)
{
}

ColorScale::~ColorScale() {}

void
ColorScale::paintEvent(QPaintEvent*)
{
    QPaintDevice* paintDevice = this;
    QPainter painter(paintDevice);
    drawFormular(
        &painter, 0, painter.window().height(), painter.window().width());
}

void
ColorScale::drawFormular(QPainter* painter, int start_point_y,
                         int height_window, int width_color_scale)
{
    painter->drawRect(rect());

    double step            = 256. / static_cast<double>(height_window);
    m_pixelsInMeter        = 1. / step;
    double accumulate_step = 0.;

    int j             = 0;
    int num_draw_line = 0;
    // Берем 256 + 1, с запасом, что бы не было недорисованного
    while (accumulate_step <= 257)
    {
        j = static_cast<int>(accumulate_step);

        // Что бы не вышли за пределы
        if (j > 255)
            j = 255;
        painter->setPen(getColor(j));
        painter->drawLine(0,
                          start_point_y + height_window - num_draw_line,
                          width_color_scale,
                          start_point_y + height_window - num_draw_line);
        accumulate_step += step;
        num_draw_line += 1;
    }

    drawScale(painter,
              255,
              width_color_scale,
              height_window,
              width_color_scale,
              start_point_y,
              32,
              3,
              true,
              false,
              true);

    drawScale(painter,
              255,
              width_color_scale,
              height_window,
              0,
              start_point_y,
              32,
              3,
              false,
              true,
              true);
    // ------------
}

void
ColorScale::drawScale(QPainter* painter, int height_values, int width_shkala,
                      int height_pixels, int start_point_x, int start_point_y,
                      int scaleStep, int kratnost_dl_riski, bool bDrawNum,
                      bool bRight, bool bReverseNum)
{
    int num_meters, smeschenie_dlja_riski, a, dist_num_to_scale,
        height_in_pixels;
    int size_font_num = 10; // в px
    int size_compensation_length
        = 3; // указывается разрядность самого большого числа, что бы двигать
             // числа по правому краю от него

    height_in_pixels = height_values * m_pixelsInMeter;
    if (height_in_pixels >= height_pixels)
    {
        height_in_pixels = height_pixels;
    }

    painter->drawLine(start_point_x,
                      start_point_y,
                      start_point_x,
                      start_point_y + height_in_pixels);

    a                     = 0;
    smeschenie_dlja_riski = (width_shkala / 2) - size_font_num;
    dist_num_to_scale     = (width_shkala / 2) + (size_font_num / 3.);

    if (!bRight)
    {
        smeschenie_dlja_riski = -smeschenie_dlja_riski;
    }

    QFont f = painter->font();
    f.setPixelSize(size_font_num);
    painter->setFont(f);

    QString str;
    int* compensation_length = new int[size_compensation_length];

    // Если риски и числа должны быть направлены в правую сторону
    if (bRight)
    {
        dist_num_to_scale = -dist_num_to_scale;
        for (int i = 0; i < size_compensation_length; i++)
        {
            compensation_length[i] = 0;
        }
    }
    else
    {
        // Увеличим этими значениями dist_num_to_scale на длинну
        // compensation_length[0] для однозначного,
        // compensation_length[1] для двухзначного,
        // compensation_length[2] для трёхзначного, и т.д. так,
        // чтобы они друг относительно друга стояли посередине
        for (int i = 0; i < size_compensation_length; i++)
        {
            compensation_length[i] = ((size_font_num / 2.) * i) / 2;
        }
    }

    for (int iMeter = 0; iMeter < height_values; iMeter += scaleStep, a++)
    {
        if (iMeter * m_pixelsInMeter > height_pixels)
        {
            break;
        }
        // Если индекс a кратен двум, то
        if ((a % kratnost_dl_riski) == 0)
        {
            // Линия подлинее (длинной smeschenie_dlja_riski * 2), пожирнее, или
            // другим цветом
            painter->setPen(QPen(QBrush(colorLabels), 1));
            painter->drawLine(start_point_x + smeschenie_dlja_riski /* * 2*/,
                              start_point_y + iMeter * m_pixelsInMeter,
                              start_point_x,
                              start_point_y + iMeter * m_pixelsInMeter);
        }
        // Иначе
        else
        {
            painter->setPen(colorLabels);
            painter->drawLine(start_point_x + smeschenie_dlja_riski,
                              start_point_y + iMeter * m_pixelsInMeter,
                              start_point_x,
                              start_point_y + iMeter * m_pixelsInMeter);
        }

        if (bDrawNum)
        {
            if (bReverseNum)
            {
                num_meters = height_values - iMeter;
            }
            else
            {
                num_meters = iMeter;
            }
            str.setNum(num_meters);

            if (num_meters < 10)
            {
                painter->drawText(
                    start_point_x - dist_num_to_scale - compensation_length[0],
                    start_point_y + iMeter * m_pixelsInMeter + size_font_num,
                    str);
            }
            else if (num_meters < 100)
            {
                painter->drawText(
                    start_point_x - dist_num_to_scale - compensation_length[1],
                    start_point_y + iMeter * m_pixelsInMeter + size_font_num,
                    str);
            }
            else
            {
                painter->drawText(
                    start_point_x - dist_num_to_scale - compensation_length[2],
                    start_point_y + iMeter * m_pixelsInMeter + size_font_num,
                    str);
            }
        }
    }
    if (bDrawNum)
    {
        painter->drawText(start_point_x - dist_num_to_scale
                              - compensation_length[0],
                          start_point_y + height_values * m_pixelsInMeter,
                          "0");
    }

    delete[] compensation_length;
}
