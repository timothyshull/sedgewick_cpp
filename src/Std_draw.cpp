#include <QtWidgets/QApplication>
#include <QtGui/QSurfaceFormat>

#include "Std_draw.h"

QApplication *Std_draw::app_ptr = nullptr;

Window *Std_draw::window_ptr = nullptr;
//void Std_draw::set_canvas_size()
//{
//
//}
//
//void Std_draw::set_canvas_size(int canvas_width, int canvas_height)
//{
//
//}

void Std_draw::init(int argc, char *argv[])
{
    static QApplication app{argc, argv};
    Std_draw::app_ptr = &app;
    auto fmt = QSurfaceFormat{};
    fmt.setSamples(4);
    QSurfaceFormat::setDefaultFormat(fmt);
    static Window window{};
    Std_draw::window_ptr = &window;
}

int Std_draw::exec()
{
    Std_draw::window_ptr->show();
    return Std_draw::app_ptr->exec();
}

//JMenuBar Std_draw::create_menu_bar()
//{
//    return nullptr;
//}
//
//void Std_draw::set_x_scale()
//{
//
//}
//
//void Std_draw::set_y_scale()
//{
//
//}
//
//void Std_draw::set_scale()
//{
//
//}
//
//void Std_draw::set_x_scale(double min, double max)
//{
//
//}
//
//void Std_draw::set_y_scale(double min, double max)
//{
//
//}
//
//void Std_draw::set_scale(double min, double max)
//{
//
//}
//
//void Std_draw::clear()
//{
//
//}
//
//void Std_draw::clear(Color &color)
//{
//
//}
//
//double Std_draw::get_pen_radius()
//{
//    return 0;
//}
//
//void Std_draw::set_pen_radius()
//{
//
//}
//
//void Std_draw::set_pen_radius(double radius)
//{
//
//}
//
//Color Std_draw::get_pen_color()
//{
//    return nullptr;
//}
//
//void Std_draw::set_pen_color()
//{
//
//}
//
//void Std_draw::set_pen_color(Color &color)
//{
//
//}
//
//void Std_draw::set_pen_color(int red, int green, int blue)
//{
//
//}
//
//Font Std_draw::get_font()
//{
//    return nullptr;
//}
//
//void Std_draw::set_font()
//{
//
//}
//
//void Std_draw::set_font(Font font)
//{
//
//}
//
//void Std_draw::line(double x0, double y0, double x1, double y1)
//{
//
//}
//
//void Std_draw::pixel(double x, double y)
//{
//
//}
//
//void Std_draw::point(double x, double y)
//{
//
//}
//
//void Std_draw::circle(double x, double y, double radius)
//{
//
//}
//
//void Std_draw::filled_circle(double x, double y, double radius)
//{
//
//}
//
//void Std_draw::ellipse(double x, double y, double semiMajorAxis, double semiMinorAxis)
//{
//
//}
//
//void Std_draw::filled_ellipse(double x, double y, double semiMajorAxis, double semiMinorAxis)
//{
//
//}
//
//void Std_draw::arc(double x, double y, double radius, double angle1, double angle2)
//{
//
//}
//
//void Std_draw::square(double x, double y, double halfLength)
//{
//
//}
//
//void Std_draw::filled_square(double x, double y, double halfLength)
//{
//
//}
//
//void Std_draw::rectangle(double x, double y, double halfWidth, double halfHeight)
//{
//
//}
//
//void Std_draw::filled_rectangle(double x, double y, double halfWidth, double halfHeight)
//{
//
//}
//
//void Std_draw::polygon(std::vector<double> const &x, std::vector<double> const &y)
//{
//
//}
//
//void Std_draw::filled_polygon(double x, double y)
//{
//
//}
//
//BufferedImage Std_draw::get_image(std::string &filename)
//{
//    return nullptr;
//}
//
//void Std_draw::picture(double x, double y, std::string filename)
//{
//
//}
//
//void Std_draw::picture(double x, double y, std::string filename, double degrees)
//{
//
//}
//
//void Std_draw::picture(double x, double y, std::string filename, double scaledWidth, double scaledHeight)
//{
//
//}
//
//void
//Std_draw::picture(double x, double y, std::string filename, double scaledWidth, double scaledHeight, double degrees)
//{
//
//}
//
//void Std_draw::text(double x, double y, std::string text)
//{
//
//}
//
//void Std_draw::text(double x, double y, std::string text, double degrees)
//{
//
//}
//
//void Std_draw::text_left(double x, double y, std::string text)
//{
//
//}
//
//void Std_draw::text_right(double x, double y, std::string text)
//{
//
//}
//
//void Std_draw::show(int t)
//{
//
//}
//
//void Std_draw::pause(int t)
//{
//
//}
//
//void Std_draw::show()
//{
//
//}
//
//void Std_draw::draw()
//{
//
//}
//
//void Std_draw::enable_double_buffering()
//{
//
//}
//
//void Std_draw::disable_double_buffering()
//{
//
//}
//
//void Std_draw::save(std::string filename)
//{
//
//}
//
//void Std_draw::action_performed(ActionEvent e)
//{
//
//}
//
//bool Std_draw::mouse_pressed()
//{
//    return false;
//}
//
//double Std_draw::mouse_x()
//{
//    return 0;
//}
//
//double Std_draw::mouse_y()
//{
//    return 0;
//}
//
//void Std_draw::mouse_clicked(MouseEvent &e)
//{
//
//}
//
//void Std_draw::mouse_entered(MouseEvent &e)
//{
//
//}
//
//void Std_draw::mouse_exited(MouseEvent &e)
//{
//
//}
//
//void Std_draw::mouse_pressed(MouseEvent &e)
//{
//
//}
//
//void Std_draw::mouse_released(MouseEvent &e)
//{
//
//}
//
//void Std_draw::mouse_dragged(MouseEvent &e)
//{
//
//}
//
//void Std_draw::mouse_moved(MouseEvent &e)
//{
//
//}
//
//bool Std_draw::has_next_key_typed()
//{
//    return false;
//}
//
//char Std_draw::next_key_typed()
//{
//    return 0;
//}
//
//bool Std_draw::is_key_pressed(int keycode)
//{
//    return false;
//}
//
//void Std_draw::key_typed(KeyEvent &e)
//{
//
//}
//
//void Std_draw::key_pressed(KeyEvent &e)
//{
//
//}
//
//void Std_draw::key_released(KeyEvent &e)
//{
//
//}

//class Std_draw {
//public:
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
//
//    Std_draw() = delete;
//
//    static void set_canvas_size()
//    {
//        set_canvas_size(DEFAULT_SIZE, DEFAULT_SIZE);
//    }
//
//    static void set_canvas_size(int canvas_width, int canvas_height)
//    {
//        if (canvas_width <= 0 || canvas_height <= 0) {
//            throw utility::Illegal_argument_exception{"width and height must be positive"};
//        }
//        width = canvas_width;
//        height = canvas_height;
//        init();
//    }
//
//    static void init()
//    {
//        if (frame != nullptr) { frame.setVisible(false); }
//        frame = JFrame();
//        _offscreen_image = BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
//        _onscreen_image = BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
//        _offscreen = _offscreen_image.createGraphics();
//        _onscreen = _onscreen_image.createGraphics();
//        set_x_scale();
//        set_y_scale();
//        _offscreen.setColor(DEFAULT_CLEAR_COLOR);
//        _offscreen.fillRect(0, 0, width, height);
//        set_pen_color();
//        set_pen_radius();
//        set_font();
//        clear();
//
//        // add antialiasing
//        RenderingHints hints = RenderingHints(RenderingHints.KEY_ANTIALIASING,
//                                              RenderingHints.VALUE_ANTIALIAS_ON);
//        hints.put(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
//        _offscreen.addRenderingHints(hints);
//
//        // frame stuff
//        ImageIcon icon = ImageIcon(_onscreen_image);
//        JLabel draw = JLabel(icon);
//
//        draw.addMouseListener(std);
//        draw.addMouseMotionListener(std);
//
//        frame.setContentPane(draw);
//        frame.addKeyListener(std);
//        frame.setResizable(false);
//        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);            // closes all windows
//        // frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);      // closes only current window
//        frame.setTitle("Standard Draw");
//        frame.setJMenuBar(create_menu_bar());
//        frame.pack();
//        frame.requestFocusInWindow();
//        frame.setVisible(true);
//    }
//
//    static JMenuBar create_menu_bar()
//    {
//        JMenuBar menuBar = new JMenuBar();
//        JMenu menu = new JMenu("File");
//        menuBar.add(menu);
//        JMenuItem menuItem1 = new JMenuItem(" Save...   ");
//        menuItem1.addActionListener(std);
//        menuItem1.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,
//                                                        Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
//        menu.add(menuItem1);
//        return menuBar;
//    }
//
//    static void set_x_scale()
//    {
//        set_x_scale(DEFAULT_XMIN, DEFAULT_XMAX);
//    }
//
//    static void set_y_scale()
//    {
//        set_y_scale(DEFAULT_YMIN, DEFAULT_YMAX);
//    }
//
//    static void set_scale()
//    {
//        set_x_scale();
//        set_y_scale();
//    }
//
//    static void set_x_scale(double min, double max)
//    {
//        double size = max - min;
//        if (size == 0.0) { throw utility::Illegal_argument_exception{"the min and max are the same"}; }
//        synchronized(_mouse_lock)
//        {
//            xmin = min - BORDER * size;
//            xmax = max + BORDER * size;
//        }
//    }
//
//    static void set_y_scale(double min, double max)
//    {
//        double size = max - min;
//        if (size == 0.0) { throw utility::Illegal_argument_exception{"the min and max are the same"}; }
//        synchronized(_mouse_lock)
//        {
//            ymin = min - BORDER * size;
//            ymax = max + BORDER * size;
//        }
//    }
//
//    static void set_scale(double min, double max)
//    {
//        double size = max - min;
//        if (size == 0.0) { throw utility::Illegal_argument_exception{"the min and max are the same"}; }
//        synchronized(_mouse_lock)
//        {
//            xmin = min - BORDER * size;
//            xmax = max + BORDER * size;
//            ymin = min - BORDER * size;
//            ymax = max + BORDER * size;
//        }
//    }
//
//    static void clear()
//    {
//        clear(DEFAULT_CLEAR_COLOR);
//    }
//
//    static void clear(Color& color)
//    {
//        _offscreen.setColor(color);
//        _offscreen.fillRect(0, 0, width, height);
//        _offscreen.setColor(penColor);
//        draw();
//    }
//
//    static double get_pen_radius()
//    {
//        return penRadius;
//    }
//
//    static void set_pen_radius()
//    {
//        set_pen_radius(DEFAULT_PEN_RADIUS);
//    }
//
//    static void set_pen_radius(double radius)
//    {
//        if (!(radius >= 0)) { throw utility::Illegal_argument_exception{"pen radius must be nonnegative"}; }
//        penRadius = radius;
//        float scaledPenRadius = (float) (radius * DEFAULT_SIZE);
//        BasicStroke stroke = new BasicStroke(scaledPenRadius, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
//        // BasicStroke stroke = new BasicStroke(scaledPenRadius);
//        _offscreen.setStroke(stroke);
//    }
//
//    static Color get_pen_color()
//    {
//        return penColor;
//    }
//
//    static void set_pen_color()
//    {
//        set_pen_color(DEFAULT_PEN_COLOR);
//    }
//
//    static void set_pen_color(Color& color)
//    {
//        if (color == nullptr) { throw utility::Null_pointer_exception{}; }
//        penColor = color;
//        _offscreen.setColor(penColor);
//    }
//
//    static void set_pen_color(int red, int green, int blue)
//    {
//        if (red < 0 || red >= 256) { throw utility::Illegal_argument_exception{"amount of red must be between 0 and 255"}; }
//        if (green < 0 || green >= 256) { throw utility::Illegal_argument_exception{"amount of green must be between 0 and 255"}; }
//        if (blue < 0 || blue >= 256) { throw utility::Illegal_argument_exception{"amount of blue must be between 0 and 255"}; }
//        set_pen_color(new Color(red, green, blue));
//    }
//
//    static Font get_font()
//    {
//        return _font;
//    }
//
//    static void set_font()
//    {
//        set_font(_default_font);
//    }
//
//    static void set_font(Font font)
//    {
//        if (font == null) { throw utility::Null_pointer_exception{}; }
//        StdDraw.font = font;
//    }
//
//    static void line(double x0, double y0, double x1, double y1)
//    {
//        _offscreen.draw(new Line2D.Double(_scale_x(x0), _scale_y(y0), _scale_x(x1), _scale_y(y1)));
//        draw();
//    }
//
//    static void pixel(double x, double y)
//    {
//        _offscreen.fillRect((int) std::round(_scale_x(x)), (int) std::round(_scale_y(y)), 1, 1);
//    }
//
//    static void point(double x, double y)
//    {
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double r = penRadius;
//        float scaledPenRadius = (float) (r * DEFAULT_SIZE);
//
//        // double ws = factorX(2*r);
//        // double hs = factorY(2*r);
//        // if (ws <= 1 && hs <= 1) pixel(x, y);
//        if (scaledPenRadius <= 1) { pixel(x, y); }
//        else {
//            _offscreen.fill(new Ellipse2D.Double(xs - scaledPenRadius / 2, ys - scaledPenRadius / 2,
//                                                 scaledPenRadius, scaledPenRadius)
//        });
//        draw();
//    }
//
//    static void circle(double x, double y, double radius)
//    {
//        if (!(radius >= 0)) { throw utility::Illegal_argument_exception{"radius must be nonnegative"}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(2 * radius);
//        double hs = _factor_y(2 * radius);
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else { _offscreen.draw(new Ellipse2D.Double(xs - ws / 2, ys - hs / 2, ws, hs) });
//        draw();
//    }
//
//    static void filled_circle(double x, double y, double radius)
//    {
//        if (!(radius >= 0)) { throw utility::Illegal_argument_exception{"radius must be nonnegative"}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(2 * radius);
//        double hs = _factor_y(2 * radius);
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else { _offscreen.fill(new Ellipse2D.Double(xs - ws / 2, ys - hs / 2, ws, hs) });
//        draw();
//    }
//
//    static void ellipse(double x, double y, double semiMajorAxis, double semiMinorAxis)
//    {
//        if (!(semiMajorAxis >= 0)) { throw utility::Illegal_argument_exception{"ellipse semimajor axis must be nonnegative"}; }
//        if (!(semiMinorAxis >= 0)) { throw utility::Illegal_argument_exception{"ellipse semiminor axis must be nonnegative"}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(2 * semiMajorAxis);
//        double hs = _factor_y(2 * semiMinorAxis);
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else { _offscreen.draw(new Ellipse2D.Double(xs - ws / 2, ys - hs / 2, ws, hs) });
//        draw();
//    }
//
//    static void filled_ellipse(double x, double y, double semiMajorAxis, double semiMinorAxis)
//    {
//        if (!(semiMajorAxis >= 0)) { throw utility::Illegal_argument_exception{"ellipse semimajor axis must be nonnegative"}; }
//        if (!(semiMinorAxis >= 0)) { throw utility::Illegal_argument_exception{"ellipse semiminor axis must be nonnegative"}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(2 * semiMajorAxis);
//        double hs = _factor_y(2 * semiMinorAxis);
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else { _offscreen.fill(new Ellipse2D.Double(xs - ws / 2, ys - hs / 2, ws, hs) });
//        draw();
//    }
//
//    static void arc(double x, double y, double radius, double angle1, double angle2)
//    {
//        if (radius < 0) { throw utility::Illegal_argument_exception{"arc radius must be nonnegative"}; }
//        while (angle2 < angle1) { angle2 += 360; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(2 * radius);
//        double hs = _factor_y(2 * radius);
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else { _offscreen.draw(new Arc2D.Double(xs - ws / 2, ys - hs / 2, ws, hs, angle1, angle2 - angle1, Arc2D.OPEN) });
//        draw();
//    }
//
//    static void square(double x, double y, double halfLength)
//    {
//        if (!(halfLength >= 0)) { throw utility::Illegal_argument_exception{"half length must be nonnegative"}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(2 * halfLength);
//        double hs = _factor_y(2 * halfLength);
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else { _offscreen.draw(new Rectangle2D.Double(xs - ws / 2, ys - hs / 2, ws, hs) });
//        draw();
//    }
//
//    static void filled_square(double x, double y, double halfLength)
//    {
//        if (!(halfLength >= 0)) { throw utility::Illegal_argument_exception{"half length must be nonnegative"}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(2 * halfLength);
//        double hs = _factor_y(2 * halfLength);
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else { _offscreen.fill(new Rectangle2D.Double(xs - ws / 2, ys - hs / 2, ws, hs) });
//        draw();
//    }
//
//    static void rectangle(double x, double y, double halfWidth, double halfHeight)
//    {
//        if (!(halfWidth >= 0)) { throw utility::Illegal_argument_exception{"half width must be nonnegative"}; }
//        if (!(halfHeight >= 0)) { throw utility::Illegal_argument_exception{"half height must be nonnegative"}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(2 * halfWidth);
//        double hs = _factor_y(2 * halfHeight);
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else { _offscreen.draw(new Rectangle2D.Double(xs - ws / 2, ys - hs / 2, ws, hs) });
//        draw();
//    }
//
//    static void filled_rectangle(double x, double y, double halfWidth, double halfHeight)
//    {
//        if (!(halfWidth >= 0)) { throw utility::Illegal_argument_exception{"half width must be nonnegative"}; }
//        if (!(halfHeight >= 0)) { throw utility::Illegal_argument_exception{"half height must be nonnegative"}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(2 * halfWidth);
//        double hs = _factor_y(2 * halfHeight);
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else { _offscreen.fill(new Rectangle2D.Double(xs - ws / 2, ys - hs / 2, ws, hs) });
//        draw();
//    }
//
//    static void polygon(double[] x, double[] y)
//    {
//        if (x == null) { throw utility::Null_pointer_exception{}; }
//        if (y == null) { throw utility::Null_pointer_exception{}; }
//        int n1 = x.length;
//        int n2 = y.length;
//        if (n1 != n2) { throw utility::Illegal_argument_exception{"arrays must be of the same length"}; }
//        int n = n1;
//        GeneralPath path = new GeneralPath();
//        path.moveTo((float) _scale_x(x[0]), (float) _scale_y(y[0]));
//        for (int i = 0; i < n; i++) {
//            path.lineTo((float) _scale_x(x[i]), (float) _scale_y(y[i]));
//        }
//        path.closePath();
//        _offscreen.draw(path);
//        draw();
//    }
//
//    static void filled_polygon(double x, double y)
//    {
//        if (x == null) { throw utility::Null_pointer_exception{}; }
//        if (y == null) { throw utility::Null_pointer_exception{}; }
//        int n1 = x.length;
//        int n2 = y.length;
//        if (n1 != n2) { throw utility::Illegal_argument_exception{"arrays must be of the same length"}; }
//        int n = n1;
//        GeneralPath path = new GeneralPath();
//        path.moveTo((float) _scale_x(x[0]), (float) _scale_y(y[0]));
//        for (int i = 0; i < n; i++) {
//            path.lineTo((float) _scale_x(x[i]), (float) _scale_y(y[i]));
//        }
//        path.closePath();
//        _offscreen.fill(path);
//        draw();
//    }
//
//    static BufferedImage get_image(std::string& filename)
//    {
//        if (filename == null) { throw utility::Null_pointer_exception{}; }
//
//        // from a file or URL
//        try {
//            URL url = new URL(filename);
//            BufferedImage image = ImageIO.read(url);
//            return image;
//        } catch (IOException e) {
//            // ignore
//        }
//
//        // in case file is inside a .jar (classpath relative to StdDraw)
//        try {
//            URL
//            url = StdDraw.
//            class.getResource(filename);
//            BufferedImage image = ImageIO.read(url);
//            return image;
//        } catch (IOException e) {
//            // ignore
//        }
//
//        // in case file is inside a .jar (classpath relative to root of jar)
//        try {
//            URL
//            url = StdDraw.
//            class.getResource("/" + filename);
//            BufferedImage image = ImageIO.read(url);
//            return image;
//        } catch (IOException e) {
//            // ignore
//        }
//        throw utility::Illegal_argument_exception{"image " + filename + " not found"};
//    }
//
//    static void picture(double x, double y, std::string filename)
//    {
//        BufferedImage image = get_image(filename);
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        int ws = image.getWidth();
//        int hs = image.getHeight();
//        if (ws < 0 || hs < 0) { throw utility::Illegal_argument_exception{"image " + filename + " is corrupt"}; }
//
//        _offscreen.drawImage(image, (int) std::round(xs - ws / 2.0), (int) std::round(ys - hs / 2.0), null);
//        draw();
//    }
//
//    static void picture(double x, double y, std::string filename, double degrees)
//    {
//        BufferedImage image = get_image(filename);
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        int ws = image.getWidth();
//        int hs = image.getHeight();
//        if (ws < 0 || hs < 0) { throw utility::Illegal_argument_exception{"image " + filename + " is corrupt"}; }
//
//        _offscreen.rotate(std::toRadians(-degrees), xs, ys);
//        _offscreen.drawImage(image, (int) std::round(xs - ws / 2.0), (int) std::round(ys - hs / 2.0), null);
//        _offscreen.rotate(std::toRadians(+degrees), xs, ys);
//
//        draw();
//    }
//
//    static void picture(double x, double y, std::string filename, double scaledWidth, double scaledHeight)
//    {
//        Image image = get_image(filename);
//        if (scaledWidth < 0) { throw utility::Illegal_argument_exception{"width is negative: " + scaledWidth}; }
//        if (scaledHeight < 0) { throw utility::Illegal_argument_exception{"height is negative: " + scaledHeight}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(scaledWidth);
//        double hs = _factor_y(scaledHeight);
//        if (ws < 0 || hs < 0) { throw utility::Illegal_argument_exception{"image " + filename + " is corrupt"}; }
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//        else {
//            _offscreen.drawImage(image, (int) std::round(xs - ws / 2.0),
//                                 (int) std::round(ys - hs / 2.0),
//                                 (int) std::round(ws),
//                                 (int) std::round(hs), null);
//        }
//        draw();
//    }
//
//    static void picture(double x, double y, std::string filename, double scaledWidth, double scaledHeight, double degrees)
//    {
//        if (scaledWidth < 0) { throw utility::Illegal_argument_exception{"width is negative: " + scaledWidth}; }
//        if (scaledHeight < 0) { throw utility::Illegal_argument_exception{"height is negative: " + scaledHeight}; }
//        Image image = get_image(filename);
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        double ws = _factor_x(scaledWidth);
//        double hs = _factor_y(scaledHeight);
//        if (ws < 0 || hs < 0) { throw utility::Illegal_argument_exception{"image " + filename + " is corrupt"}; }
//        if (ws <= 1 && hs <= 1) { pixel(x, y); }
//
//        _offscreen.rotate(std::toRadians(-degrees), xs, ys);
//        _offscreen.drawImage(image, (int) std::round(xs - ws / 2.0),
//                             (int) std::round(ys - hs / 2.0),
//                             (int) std::round(ws),
//                             (int) std::round(hs), null);
//        _offscreen.rotate(std::toRadians(+degrees), xs, ys);
//
//        draw();
//    }
//
//    static void text(double x, double y, std::string text)
//    {
//        if (text == null) { throw utility::Null_pointer_exception{}; }
//        _offscreen.setFont(_font);
//        FontMetrics metrics = _offscreen.getFontMetrics();
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        int ws = metrics.stringWidth(text);
//        int hs = metrics.getDescent();
//        _offscreen.drawstd::string(text, (float) (xs - ws / 2.0), (float) (ys + hs));
//        draw();
//    }
//
//    static void text(double x, double y, std::string text, double degrees)
//    {
//        if (text == null) { throw utility::Null_pointer_exception{}; }
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        _offscreen.rotate(std::toRadians(-degrees), xs, ys);
//        text(x, y, text);
//        _offscreen.rotate(std::toRadians(+degrees), xs, ys);
//    }
//
//    static void text_left(double x, double y, std::string text)
//    {
//        if (text == null) { throw utility::Null_pointer_exception{}; }
//        _offscreen.setFont(_font);
//        FontMetrics metrics = _offscreen.getFontMetrics();
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        int hs = metrics.getDescent();
//        _offscreen.drawstd::string(text, (float) xs, (float) (ys + hs));
//        draw();
//    }
//
//    static void text_right(double x, double y, std::string text)
//    {
//        if (text == null) { throw utility::Null_pointer_exception{}; }
//        _offscreen.setFont(_font);
//        FontMetrics metrics = _offscreen.getFontMetrics();
//        double xs = _scale_x(x);
//        double ys = _scale_y(y);
//        int ws = metrics.stringWidth(text);
//        int hs = metrics.getDescent();
//        _offscreen.drawstd::string(text, (float) (xs - ws), (float) (ys + hs));
//        draw();
//    }
//
//    static void show(int t)
//    {
//        // sleep until the next time we're allowed to draw
//        long millis = System.currentTimeMillis();
//        if (millis < _next_draw) {
//            try {
//                Thread.sleep(_next_draw - millis);
//            } catch (InterruptedException e) {
//                System.out.println("Error sleeping");
//            }
//            millis = _next_draw;
//        }
//
//        show();
//        enable_double_buffering();
//
//        // when are we allowed to draw again
//        _next_draw = millis + t;
//    }
//
//    static void pause(int t)
//    {
//        // sleep until the next time we're allowed to draw
//        long millis = System.currentTimeMillis();
//        if (millis < _next_draw) {
//            try {
//                Thread.sleep(_next_draw - millis);
//            } catch (InterruptedException e) {
//                System.out.println("Error sleeping");
//            }
//            millis = _next_draw;
//        }
//
//        // when are we allowed to draw again
//        _next_draw = millis + t;
//    }
//
//    static void show()
//    {
//        _onscreen.drawImage(_offscreen_image, 0, 0, nullptr);
//        frame.repaint();
//    }
//
//    static void draw()
//    {
//        if (!defer) { show(); }
//    }
//
//    static void enable_double_buffering()
//    {
//        defer = true;
//    }
//
//    static void disable_double_buffering()
//    {
//        defer = false;
//    }
//
//    static void save(std::string filename)
//    {
//        if (filename == null) { throw utility::Null_pointer_exception{}; }
//        File file = new File(filename);
//        std::string suffix = filename.substring(filename.lastIndexOf('.') + 1);
//
//        // png files
//        if (suffix.toLowerCase().equals("png")) {
//            try {
//                ImageIO.write(_onscreen_image, suffix, file);
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }
//
//            // need to change from ARGB to RGB for JPEG
//            // reference: http://archives.java.sun.com/cgi-bin/wa?A2=ind0404&L=java2d-interest&D=0&P=2727
//        else if (suffix.toLowerCase().equals("jpg")) {
//            WritableRaster raster = _onscreen_image.getRaster();
//            WritableRaster newRaster;
//            newRaster = raster.createWritableChild(0, 0, width, height, 0, 0, new int[]{0, 1, 2});
//            DirectColorModel cm = (DirectColorModel) _onscreen_image.getColorModel();
//            DirectColorModel newCM = new DirectColorModel(cm.getPixelSize(),
//                                                          cm.getRedMask(),
//                                                          cm.getGreenMask(),
//                                                          cm.getBlueMask());
//            BufferedImage rgbBuffer = new BufferedImage(newCM, newRaster, false, null);
//            try {
//                ImageIO.write(rgbBuffer, suffix, file);
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        } else {
//            System.out.println("Invalid image file type: " + suffix);
//        }
//    }
//
//    void action_performed(ActionEvent e)
//    {
//        FileDialog chooser = new FileDialog(StdDraw.frame, "Use a .png or .jpg extension", FileDialog.SAVE);
//        chooser.setVisible(true);
//        std::string filename = chooser.getFile();
//        if (filename != null) {
//            StdDraw.save(chooser.getDirectory() + File.separator + chooser.getFile());
//        }
//    }
//
//    static bool mouse_pressed()
//    {
//        synchronized(_mouse_lock)
//        {
//            return _mouse_pressed;
//        }
//    }
//
//    static double mouse_x()
//    {
//        synchronized(_mouse_lock)
//        {
//            return mouse_x;
//        }
//    }
//
//    static double mouse_y()
//    {
//        synchronized(_mouse_lock)
//        {
//            return mouse_y;
//        }
//    }
//
//    void mouse_clicked(MouseEvent& e) {}
//
//    void mouse_entered(MouseEvent& e)
//    {
//    }
//
//    void mouse_exited(MouseEvent& e)
//    {
//    }
//
//    void mouse_pressed(MouseEvent& e)
//    {
//        synchronized(_mouse_lock)
//        {
//            mouse_x = user_x(e.getX());
//            mouse_y = user_y(e.getY());
//            _mouse_pressed = true;
//        }
//    }
//
//    void mouse_released(MouseEvent& e)
//    {
//        synchronized(_mouse_lock)
//        {
//            _mouse_pressed = false;
//        }
//    }
//
//    void mouse_dragged(MouseEvent& e)
//    {
//        synchronized(_mouse_lock)
//        {
//            mouse_x = StdDraw.userX(e.getX());
//            mouse_y = StdDraw.userY(e.getY());
//        }
//    }
//
//    void mouse_moved(MouseEvent& e)
//    {
//        synchronized(_mouse_lock)
//        {
//            mouse_x = StdDraw.userX(e.getX());
//            mouse_y = StdDraw.userY(e.getY());
//        }
//    }
//
//    static bool has_next_key_typed()
//    {
//        synchronized(_key_lock)
//        {
//            return !_keys_typed.isEmpty();
//        }
//    }
//
//    static char next_key_typed()
//    {
//        synchronized(_key_lock)
//        {
//            if (_keys_typed.isEmpty()) {
//                throw new NoSuchElementException("your program has already processed all keystrokes");
//            }
//            return _keys_typed.removeLast();
//        }
//    }
//
//    static bool is_key_pressed(int keycode)
//    {
//        synchronized(_key_lock)
//        {
//            return _keys_down.contains(keycode);
//        }
//    }
//
//    void key_typed(KeyEvent& e)
//    {
//        synchronized(_key_lock)
//        {
//            _keys_typed.addFirst(e.getKeyChar());
//        }
//    }
//
//    void key_pressed(KeyEvent& e)
//    {
//        synchronized(_key_lock)
//        {
//            _keys_down.add(e.getKeyCode());
//        }
//    }
//
//    void key_released(KeyEvent& e)
//    {
//        synchronized(_key_lock)
//        {
//            _keys_down.remove(e.getKeyCode());
//        }
//    }
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
