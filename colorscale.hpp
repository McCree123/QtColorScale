#ifndef COLORSCALE_HPP
#define COLORSCALE_HPP

#include <QPainter>
#include <QWidget>

class ColorScale : public QWidget
{
    Q_OBJECT
private:
    double m_pixelsInMeter = 1.0f;

    // Цвет рисок и подписей шкал по умолчанию
    QColor colorLabels{70, 240, 210};

    const QRgb indicator_256[256]
        = {QRgb(0x000000), QRgb(0x0d0d0e), QRgb(0x0c0c0f), QRgb(0x0c0c10),
           QRgb(0x0c0c10), QRgb(0x0c0c10), QRgb(0x0d0d11), QRgb(0x0e0e12),
           QRgb(0x0e0e13), QRgb(0x0e0e13), QRgb(0x0e0e13), QRgb(0x0e0e14),
           QRgb(0x100e16), QRgb(0x100e17), QRgb(0x101019), QRgb(0x10101a),
           QRgb(0x10101a), QRgb(0x11101b), QRgb(0x12101b), QRgb(0x12101e),
           QRgb(0x13101f), QRgb(0x131021), QRgb(0x131022), QRgb(0x151223),
           QRgb(0x151225), QRgb(0x151226), QRgb(0x161228), QRgb(0x161228),
           QRgb(0x17122a), QRgb(0x17122b), QRgb(0x19132f), QRgb(0x191330),
           QRgb(0x1a1332), QRgb(0x1a1333), QRgb(0x1b1535), QRgb(0x1c1537),
           QRgb(0x1c1538), QRgb(0x1d153b), QRgb(0x1d153c), QRgb(0x1e153e),
           QRgb(0x1e1540), QRgb(0x1f1644), QRgb(0x201645), QRgb(0x201646),
           QRgb(0x211648), QRgb(0x211649), QRgb(0x22164b), QRgb(0x23164e),
           QRgb(0x241652), QRgb(0x241753), QRgb(0x251755), QRgb(0x251757),
           QRgb(0x261758), QRgb(0x26175c), QRgb(0x26175e), QRgb(0x271760),
           QRgb(0x271762), QRgb(0x271764), QRgb(0x281666), QRgb(0x28166a),
           QRgb(0x28166b), QRgb(0x29166c), QRgb(0x29166f), QRgb(0x281870),
           QRgb(0x271d71), QRgb(0x261f72), QRgb(0x262272), QRgb(0x252473),
           QRgb(0x252673), QRgb(0x242873), QRgb(0x232a74), QRgb(0x212d74),
           QRgb(0x212e74), QRgb(0x203074), QRgb(0x1f3274), QRgb(0x1e3374),
           QRgb(0x1b3675), QRgb(0x193875), QRgb(0x163b75), QRgb(0x143c75),
           QRgb(0x123d76), QRgb(0x103f75), QRgb(0x0c4175), QRgb(0x0a4275),
           QRgb(0x074475), QRgb(0x054475), QRgb(0x024574), QRgb(0x004774),
           QRgb(0x004974), QRgb(0x004c74), QRgb(0x004d74), QRgb(0x004e74),
           QRgb(0x004f74), QRgb(0x005174), QRgb(0x005373), QRgb(0x005472),
           QRgb(0x005572), QRgb(0x005672), QRgb(0x005771), QRgb(0x005a71),
           QRgb(0x005b71), QRgb(0x005c70), QRgb(0x005d70), QRgb(0x005e70),
           QRgb(0x005f70), QRgb(0x00616f), QRgb(0x00636e), QRgb(0x00636d),
           QRgb(0x00656d), QRgb(0x00666c), QRgb(0x00676c), QRgb(0x00686b),
           QRgb(0x006a6a), QRgb(0x006b69), QRgb(0x006c69), QRgb(0x006d68),
           QRgb(0x006e68), QRgb(0x007066), QRgb(0x007165), QRgb(0x007264),
           QRgb(0x007363), QRgb(0x007462), QRgb(0x007561), QRgb(0x007860),
           QRgb(0x00795f), QRgb(0x007a5e), QRgb(0x007b5d), QRgb(0x007c5c),
           QRgb(0x007e5a), QRgb(0x007f59), QRgb(0x008157), QRgb(0x008156),
           QRgb(0x008255), QRgb(0x008454), QRgb(0x008652), QRgb(0x008750),
           QRgb(0x00884f), QRgb(0x00894e), QRgb(0x008a4d), QRgb(0x008c4b),
           QRgb(0x008e47), QRgb(0x008f45), QRgb(0x009044), QRgb(0x009142),
           QRgb(0x009240), QRgb(0x00923f), QRgb(0x00933e), QRgb(0x00933e),
           QRgb(0x00943d), QRgb(0x00943d), QRgb(0x00943d), QRgb(0x00933c),
           QRgb(0x00933b), QRgb(0x00943b), QRgb(0x00943a), QRgb(0x00933a),
           QRgb(0x0c9339), QRgb(0x1b9339), QRgb(0x309238), QRgb(0x379238),
           QRgb(0x409237), QRgb(0x449237), QRgb(0x499236), QRgb(0x519236),
           QRgb(0x569235), QRgb(0x5b9235), QRgb(0x5f9134), QRgb(0x639034),
           QRgb(0x669033), QRgb(0x6f8f32), QRgb(0x718f32), QRgb(0x758e32),
           QRgb(0x788e31), QRgb(0x7c8e30), QRgb(0x808d30), QRgb(0x848d2f),
           QRgb(0x888c2f), QRgb(0x8b8c2e), QRgb(0x918c2d), QRgb(0x938b2c),
           QRgb(0x968b2c), QRgb(0x9c892c), QRgb(0x9f882c), QRgb(0xa2882b),
           QRgb(0xa4872b), QRgb(0xaa872a), QRgb(0xad862a), QRgb(0xb38527),
           QRgb(0xb68526), QRgb(0xb98526), QRgb(0xbd8425), QRgb(0xbf8324),
           QRgb(0xc78123), QRgb(0xca8123), QRgb(0xcf8023), QRgb(0xd27f22),
           QRgb(0xd57e20), QRgb(0xda7d1e), QRgb(0xe07b1c), QRgb(0xe57a1a),
           QRgb(0xe77919), QRgb(0xe77a19), QRgb(0xe87b19), QRgb(0xe87e1a),
           QRgb(0xe8801b), QRgb(0xe9811b), QRgb(0xe9831b), QRgb(0xe9851b),
           QRgb(0xea871c), QRgb(0xea881c), QRgb(0xeb8c1d), QRgb(0xeb8d1d),
           QRgb(0xec8f1e), QRgb(0xec8f1e), QRgb(0xec911e), QRgb(0xec931e),
           QRgb(0xed951f), QRgb(0xed981b), QRgb(0xee9918), QRgb(0xee9c11),
           QRgb(0xef9d0d), QRgb(0xef9e0a), QRgb(0xf0a201), QRgb(0xf0a400),
           QRgb(0xf1a600), QRgb(0xf1a700), QRgb(0xf2aa00), QRgb(0xf3ac00),
           QRgb(0xf3af00), QRgb(0xf3af00), QRgb(0xf4b100), QRgb(0xf4b400),
           QRgb(0xf5b500), QRgb(0xf6ba00), QRgb(0xf6bb00), QRgb(0xf7bf00),
           QRgb(0xf7c000), QRgb(0xf8c300), QRgb(0xf8c500), QRgb(0xf9c700),
           QRgb(0xf9ca00), QRgb(0xf9cb00), QRgb(0xface00), QRgb(0xfacf00),
           QRgb(0xfbd400), QRgb(0xfbd700), QRgb(0xfcda00), QRgb(0xfcdc00),
           QRgb(0xfcde00), QRgb(0xfde200), QRgb(0xfde400), QRgb(0xfee900),
           QRgb(0xfeea00), QRgb(0xffee00), QRgb(0xffff00), QRgb(0xff0000)};

    QColor getColor(unsigned char strength) { return QColor(getRgb(strength)); }

    QRgb getRgb(unsigned char strength) { return indicator_256[strength]; }

public:
    explicit ColorScale(QWidget* parent = nullptr);
    virtual ~ColorScale() override;

    virtual void paintEvent(QPaintEvent*) override;

    void drawFormular(QPainter* painter, int start_point_y, int height_window,
                      int width_color_scale);

    void drawScale(QPainter* painter, int height_values, int width_shkala,
                   int height_pixels, int start_point_x, int start_point_y,
                   int scaleStep, int kratnost_dl_riski, bool bDrawNum,
                   bool bRight = true, bool bReverseNum = true);

    // Получить цвет рисок и подписей шкал
    QColor getColorLabels() const;

    // Установить цвет рисок и подписей шкал
    void setColorLabels(const QColor& value);
};

#endif // COLORSCALE_HPP
