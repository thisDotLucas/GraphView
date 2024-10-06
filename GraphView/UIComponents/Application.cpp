#include "Application.h"
#include "../Utils/Colors.h"
#include <QStyleFactory>

int QtApplication::run()
{
    m_application.setStyle(QStyleFactory::create("Fusion"));

    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, COLOR_LIGHT_GRAY);
    lightPalette.setColor(QPalette::WindowText, COLOR_BLACK);
    lightPalette.setColor(QPalette::Base, COLOR_WHITE);
    lightPalette.setColor(QPalette::AlternateBase, COLOR_DARK_GRAY);
    lightPalette.setColor(QPalette::ToolTipBase, COLOR_WHITE);
    lightPalette.setColor(QPalette::ToolTipText, COLOR_BLACK);
    lightPalette.setColor(QPalette::Text, COLOR_BLACK);
    lightPalette.setColor(QPalette::Button, COLOR_LIGHT_GRAY);
    lightPalette.setColor(QPalette::ButtonText, COLOR_BLACK);
    lightPalette.setColor(QPalette::BrightText, QColor(255, 0, 0));
    lightPalette.setColor(QPalette::Link, COLOR_BLUE_LINK);
    lightPalette.setColor(QPalette::Highlight, COLOR_HIGHLIGHT);
    lightPalette.setColor(QPalette::HighlightedText, COLOR_BLACK);

    m_application.setPalette(lightPalette);

    m_application.setStyleSheet(
        "QMainWindow { background-color: #F0F0F0; }"
        "QToolBar { background-color: #E0E0E0; border: none; padding: 5px; }"
        "QToolButton { color: black; background-color: #F0F0F0; padding: 3px 8px; border: 1px solid #D0D0D0; border-radius: 0px; }"
        "QToolButton:hover { background-color: #E0E0E0; }"
        "QToolButton:pressed { background-color: #D0D0D0; }"
        "QLabel { font-size: 16px; color: #000000; }"
        "QMenu { background-color: #F0F0F0; color: black; }"
        "QMenu::item:selected { background-color: #E0E0E0; }"
        "QStatusBar { background-color: #F0F0F0; color: #000000; }"
    );

	return m_application.exec();
}