#ifndef STD_DRAW_H
#define STD_DRAW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/qevent.h>

#include <QBrush>
#include <QFont>
#include <QPen>

#include "utility.h"
#include "Set.h"

#include <QtWidgets/QOpenGLWidget>

class Helper {
public:
    Helper()
    {
        auto gradient = QLinearGradient{QPointF(50, -20), QPointF(80, 20)};
        gradient.setColorAt(0.0, Qt::white);
        gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

        background = QBrush(QColor(64, 32, 64));
        circleBrush = QBrush(gradient);
        circlePen = QPen(Qt::black);
        circlePen.setWidth(1);
        textPen = QPen(Qt::white);
        textFont.setPixelSize(50);
    }

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed)
    {
        painter->fillRect(event->rect(), background);
        painter->translate(100, 100);

        painter->save();
        painter->setBrush(circleBrush);
        painter->setPen(circlePen);
        painter->rotate(elapsed * 0.030);

        qreal r = elapsed / 1000.0;
        int n = 30;
        for (int i = 0; i < n; ++i) {
            painter->rotate(30);
            qreal factor = (i + r) / n;
            qreal radius = 0 + 120.0 * factor;
            qreal circleRadius = 1 + factor * 20;
            painter->drawEllipse(QRectF(radius, -circleRadius,
                                        circleRadius * 2, circleRadius * 2
            ));
        }
        painter->restore();

        painter->setPen(textPen);
        painter->setFont(textFont);
        painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));
    }

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
};

class GLWidget : public QOpenGLWidget {
Q_OBJECT

public:
    GLWidget(Helper *helper, QWidget *parent)
            : QOpenGLWidget(parent), helper(helper)
    {
        elapsed = 0;
        setFixedSize(200, 200);
        setAutoFillBackground(false);
    }

public slots:

    void animate()
    {
        elapsed = (elapsed + qobject_cast<QTimer *>(sender())->interval()) % 1000;
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter;
        painter.begin(this);
        painter.setRenderHint(QPainter::Antialiasing);
        helper->paint(&painter, event, elapsed);
        painter.end();
    }

private:
    Helper *helper;
    int elapsed;
};

class Widget : public QWidget {
Q_OBJECT

public:
    Widget(Helper *helper, QWidget *parent)
            : QWidget(parent), helper(helper)
    {
        elapsed = 0;
        setFixedSize(200, 200);
    }

public slots:

    void animate()
    {
        elapsed = (elapsed + qobject_cast<QTimer *>(sender())->interval()) % 1000;
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter;
        painter.begin(this);
        painter.setRenderHint(QPainter::Antialiasing);
        helper->paint(&painter, event, elapsed);
        painter.end();
    }

private:
    Helper *helper;
    int elapsed;
};

class Window : public QWidget {
Q_OBJECT

public:
    Window()
    {
        // setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));

        native = new Widget(&helper, this);
        openGL = new GLWidget(&helper, this);
        layout = new QGridLayout;
    }

    void setup_widgets()
    {
        layout->addWidget(native, 0, 0);
        layout->addWidget(openGL, 0, 1);
    }

    void setup_labels()
    {
        auto nativeLabel = new QLabel(tr("Native"));
        nativeLabel->setAlignment(Qt::AlignHCenter);
        auto openGLLabel = new QLabel(tr("OpenGL"));
        openGLLabel->setAlignment(Qt::AlignHCenter);
        layout->addWidget(nativeLabel, 1, 0);
        layout->addWidget(openGLLabel, 1, 1);
    }

    void set_layout()
    {
        setLayout(layout);
    }

    void set_timers()
    {
        auto timer = new QTimer(this);
        connect(timer, &QTimer::timeout, native, &Widget::animate);
        connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
        timer->start(50);
    }

private:
    Helper helper;
    Widget *native;
    GLWidget *openGL;
    QGridLayout *layout;
};

class Std_draw {
private:
    using Color = QColor;
    static QApplication *app_ptr;
//    static QSurfaceFormat fmt;
    static Window *window_ptr;

public:
//    static const Color black = Color{0, 0, 0};
//    static const Color blue = Color{0, 0, 255};
//    static const Color cyan = Color{0, 255, 255};
//    static const Color dark_gray = Color{64, 64, 64};
//    static const Color gray = Color{128, 128, 128};
//    static const Color green = Color{0, 255, 0};
//    static const Color light_gray = Color{192, 192, 192};
//    static const Color magenta = Color{255, 0, 255};
//    static const Color orange = Color{255, 200, 0};
//    static const Color pink = Color{255, 175, 175};
//    static const Color red = Color{255, 0, 0};
//    static const Color white = Color{255, 255, 255};
//    static const Color yellow = Color{255, 255, 0};
//    static const Color book_blue = Color{9, 90, 166};
//    static const Color book_light_blue = Color{103, 198, 243};
//    static const Color book_red = Color{150, 35, 31};

    Std_draw() = delete;

//    static void set_canvas_size();
//
//    static void set_canvas_size(int canvas_width, int canvas_height);
//
    static void init(int argc, char *argv[]);

    static int exec();


    static void setup_widgets() {
        window_ptr->setup_widgets();
    }

    static void setup_labels() {
        window_ptr->setup_labels();
    }

    static void set_layout() {
        window_ptr->set_layout();
    }

    static void set_timers() {
        window_ptr->set_timers();
    }
//
//    static JMenuBar create_menu_bar();
//
//    static void set_x_scale();
//
//    static void set_y_scale();
//
//    static void set_scale();
//
//    static void set_x_scale(double min, double max);
//
//    static void set_y_scale(double min, double max);
//
//    static void set_scale(double min, double max);
//
//    static void clear();
//
//    static void clear(Color &color);
//
//    static double get_pen_radius();
//
//    static void set_pen_radius();
//
//    static void set_pen_radius(double radius);
//
//    static Color get_pen_color();
//
//    static void set_pen_color();
//
//    static void set_pen_color(Color &color);
//
//    static void set_pen_color(int red, int green, int blue);
//
//    static Font get_font();
//
//    static void set_font();
//
//    static void set_font(Font font);
//
//    static void line(double x0, double y0, double x1, double y1);
//
//    static void pixel(double x, double y);
//
//    static void point(double x, double y);
//
//    static void circle(double x, double y, double radius);
//
//    static void filled_circle(double x, double y, double radius);
//
//    static void ellipse(double x, double y, double semiMajorAxis, double semiMinorAxis);
//
//    static void filled_ellipse(double x, double y, double semiMajorAxis, double semiMinorAxis);
//
//    static void arc(double x, double y, double radius, double angle1, double angle2);
//
//    static void square(double x, double y, double halfLength);
//
//    static void filled_square(double x, double y, double halfLength);
//
//    static void rectangle(double x, double y, double halfWidth, double halfHeight);
//
//    static void filled_rectangle(double x, double y, double halfWidth, double halfHeight);
//
//    static void polygon(std::vector<double> const &x, std::vector<double> const &y);
//
//    static void filled_polygon(double x, double y);
//
//    static BufferedImage get_image(std::string &filename);
//
//    static void picture(double x, double y, std::string filename);
//
//    static void picture(double x, double y, std::string filename, double degrees);
//
//    static void picture(double x, double y, std::string filename, double scaledWidth, double scaledHeight);
//
//    static void
//    picture(double x, double y, std::string filename, double scaledWidth, double scaledHeight, double degrees);
//
//    static void text(double x, double y, std::string text);
//
//    static void text(double x, double y, std::string text, double degrees);
//
//    static void text_left(double x, double y, std::string text);
//
//    static void text_right(double x, double y, std::string text);
//
//    static void show(int t);
//
//    static void pause(int t);
//
//    static void show();
//
//    static void draw();
//
//    static void enable_double_buffering();
//
//    static void disable_double_buffering();
//
//    static void save(std::string filename);
//
//    void action_performed(ActionEvent e);
//
//    static bool mouse_pressed();
//
//    static double mouse_x();
//
//    static double mouse_y();
//
//    void mouse_clicked(MouseEvent &e);
//
//    void mouse_entered(MouseEvent &e);
//
//    void mouse_exited(MouseEvent &e);
//
//    void mouse_pressed(MouseEvent &e);
//
//    void mouse_released(MouseEvent &e);
//
//    void mouse_dragged(MouseEvent &e);
//
//    void mouse_moved(MouseEvent &e);
//
//    static bool has_next_key_typed();
//
//    static char next_key_typed();
//
//    static bool is_key_pressed(int keycode);
//
//    void key_typed(KeyEvent &e);
//
//    void key_pressed(KeyEvent &e);
//
//    void key_released(KeyEvent &e);
//
//private:
//    static const Color DEFAULT_PEN_COLOR = black;
//    static const Color DEFAULT_CLEAR_COLOR = white;
//    static Color penColor;
//    static const int DEFAULT_SIZE = 512;
//    static int width = DEFAULT_SIZE;
//    static int height = DEFAULT_SIZE;
//    static const double DEFAULT_PEN_RADIUS = 0.002;
//    static double penRadius;
//    static bool defer = false;
//    static const double BORDER = 0.00;
//    static const double DEFAULT_XMIN = 0.0;
//    static const double DEFAULT_XMAX = 1.0;
//    static const double DEFAULT_YMIN = 0.0;
//    static const double DEFAULT_YMAX = 1.0;
//    static double xmin, ymin, xmax, ymax;
//
//    static Object _mouse_lock = new Object();
//    static Object _key_lock = new Object();
//
//    static const Font _default_font = new Font("SansSerif", Font.PLAIN, 16);
//
//    static Font _font;
//
//    static BufferedImage _offscreen_image;
//    static BufferedImage _onscreen_image;
//    static Graphics2D _offscreen;
//    static Graphics2D _onscreen;
//
//    static Std_draw std{};
//
//    static JFrame frame;
//
//    static bool _mouse_pressed = false;
//    static double _mouse_x = 0;
//    static double _mouse_y = 0;
//
//    static List<char> _keys_typed;
//
//    static Set<int> _keys_down;
//
//    static long _next_draw = -1;
//
//    inline static double _scale_x(double x) const { return width * (x - xmin) / (xmax - xmin); }
//
//    inline static double _scale_y(double y) const { return height * (ymax - y) / (ymax - ymin); }
//
//    inline static double _factor_x(double w) const { return w * width / std::abs(xmax - xmin); }
//
//    inline static double _factor_y(double h) const { return h * height / std::abs(ymax - ymin); }
//
//    inline static double _user_x(double x) const { return xmin + x * (xmax - xmin) / width; }
//
//    inline static double _user_y(double y) const { return ymax - y * (ymax - ymin) / height; }
};

#endif // STD_DRAW_H
