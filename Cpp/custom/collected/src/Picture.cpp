#include "Picture.h"

Picture::Picture(int width, int height)
{
    if (width < 0) throw new IllegalArgumentException("width must be nonnegative");
    if (height < 0) throw new IllegalArgumentException("height must be nonnegative");
    this.width = width;
    this.height = height;
    image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
    // set to TYPE_INT_ARGB to support transparency
    filename = width + "-by-" + height;
}

Picture::Picture(Picture& picture)
{
    width = picture.width();
    height = picture.height();
    image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
    filename = picture.filename;
    for (int col = 0; col < width(); col++)
        for (int row = 0; row < height(); row++)
            image.setRGB(col, row, picture.get(col, row).getRGB());
}

Picture::Picture(File& file)
{
    this.filename = filename;
    try {
        // try to read from file in working directory
        File file = new File(filename);
        if (file.isFile()) {
            image = ImageIO.read(file);
        }

            // now try to read from file in same directory as this .class file
        else {
            URL url = getClass().getResource(filename);
            if (url == null) {
                url = new URL(filename);
            }
            image = ImageIO.read(url);
        }

        if (image == null) {
            throw new IllegalArgumentException("Invalid image file: " + filename);
        }

        width = image.getWidth(null);
        height = image.getHeight(null);
    } catch (IOException e) {
        // e.printStackTrace();
        throw new RuntimeException("Could not open file: " + filename);
    }
}

Label Picture::getJLabel()
{
    try {
        image = ImageIO.read(file);
    } catch (IOException e) {
        e.printStackTrace();
        throw new RuntimeException("Could not open file: " + file);
    }
    if (image == null) {
        throw new RuntimeException("Invalid image file: " + file);
    }
    width = image.getWidth(null);
    height = image.getHeight(null);
    filename = file.getName();
}

void Picture::setOriginUpperLeft()
{
    if (image == null) return null;         // no image available
    ImageIcon icon = new ImageIcon(image);
    return new JLabel(icon);
}

void Picture::show()
{
    if (frame == null) {
        frame = new JFrame();

        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("File");
        menuBar.add(menu);
        JMenuItem menuItem1 = new JMenuItem(" Save...   ");
        menuItem1.addActionListener(this);
        menuItem1.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,
                                                        Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        menu.add(menuItem1);
        frame.setJMenuBar(menuBar);


        frame.setContentPane(getJLabel());
        // f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setTitle(filename);
        frame.setResizable(false);
        frame.pack();
        frame.setVisible(true);
    }

    // draw
    frame.repaint();
}

Color Picture::get(int col, int row)
{
    if (col < 0 || col >= width())
        throw new IndexOutOfBoundsException("col must be between 0 and " + (width() - 1) + ": " + col);
    if (row < 0 || row >= height())
        throw new IndexOutOfBoundsException("row must be between 0 and " + (height() - 1) + ": " + col);
    if (isOriginUpperLeft) return new Color(image.getRGB(col, row));
    else return new Color(image.getRGB(col, height - row - 1));
}

void Picture::set(int col, int row, Color& color)
{
    if (col < 0 || col >= width())
        throw new IndexOutOfBoundsException("col must be between 0 and " + (width() - 1) + ": " + col);
    if (row < 0 || row >= height())
        throw new IndexOutOfBoundsException("row must be between 0 and " + (height() - 1) + ": " + row);
    if (color == null) throw new NullPointerException("can't set Color to null");
    if (isOriginUpperLeft) image.setRGB(col, row, color.getRGB());
    else image.setRGB(col, height - row - 1, color.getRGB());
}

bool Picture::operator==(const Picture& rhs)
{
    if (other == this) return true;
    if (other == null) return false;
    if (other.getClass() != this.getClass()) return false;
    Picture that = (Picture) other;
    if (this.width() != that.width()) return false;
    if (this.height() != that.height()) return false;
    for (int col = 0; col < width(); col++)
        for (int row = 0; row < height(); row++)
            if (!this.get(col, row).equals(that.get(col, row))) return false;
    return true;
}

void Picture::save(std::string& filename) {
    save(File(filename));
}

void Picture::save(File& file)
{
    filename = file.getName();
    if (frame != null) frame.setTitle(filename);
    String suffix = filename.substring(filename.lastIndexOf('.') + 1);
    suffix = suffix.toLowerCase();
    if (suffix.equals("jpg") || suffix.equals("png")) {
        try {
            ImageIO.write(image, suffix, file);
        } catch (IOException e) {
            e.printStackTrace();
        }
    } else {
        System.out.println("Error: filename must end in .jpg or .png");
    }
}

void Picture::action_performed(Action_event& e)
{
    FileDialog chooser = new FileDialog(frame,
                                        "Use a .png or .jpg extension", FileDialog.SAVE);
    chooser.setVisible(true);
    if (chooser.getFile() != null) {
        save(chooser.getDirectory() + File.separator + chooser.getFile());
    }
}
