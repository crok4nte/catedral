#include <Util/ColorText.h>

QString CatedralNamespace::Util::ColorText::Colors::Hex::Background    = "#0E0E10";
QString CatedralNamespace::Util::ColorText::Colors::Hex::Foreground    = "#E6E6E6";
QString CatedralNamespace::Util::ColorText::Colors::Hex::Comment       = "#9A9AA0";
QString CatedralNamespace::Util::ColorText::Colors::Hex::CurrentLine   = "#2A2A2E";

QString CatedralNamespace::Util::ColorText::Colors::Hex::Cyan          = "#5BC0EB";
QString CatedralNamespace::Util::ColorText::Colors::Hex::Green         = "#3FB950";
QString CatedralNamespace::Util::ColorText::Colors::Hex::Orange        = "#D29922";
QString CatedralNamespace::Util::ColorText::Colors::Hex::Pink          = "#E5484D";
QString CatedralNamespace::Util::ColorText::Colors::Hex::Purple        = "#C13C3F";
QString CatedralNamespace::Util::ColorText::Colors::Hex::Red           = "#E5484D";
QString CatedralNamespace::Util::ColorText::Colors::Hex::Yellow        = "#F2C94C";

QString CatedralNamespace::Util::ColorText::Colors::Hex::SessionCyan   = "#3A6E80";
QString CatedralNamespace::Util::ColorText::Colors::Hex::SessionGreen  = "#1C5F11";
QString CatedralNamespace::Util::ColorText::Colors::Hex::SessionOrange = "#8A5A1B";
QString CatedralNamespace::Util::ColorText::Colors::Hex::SessionPink   = "#9C2E2B";
QString CatedralNamespace::Util::ColorText::Colors::Hex::SessionPurple = "#36365b";
QString CatedralNamespace::Util::ColorText::Colors::Hex::SessionRed    = "#5b3d3e";
QString CatedralNamespace::Util::ColorText::Colors::Hex::SessionYellow = "#8A7A1B";

void CatedralNamespace::Util::ColorText::SetCatedralCarbon()
{
    CatedralNamespace::Util::ColorText::Colors::Hex::Background  = "#0E0E10";
    CatedralNamespace::Util::ColorText::Colors::Hex::Foreground  = "#E6E6E6";
    CatedralNamespace::Util::ColorText::Colors::Hex::Comment     = "#9A9AA0";
    CatedralNamespace::Util::ColorText::Colors::Hex::CurrentLine = "#2A2A2E";

    CatedralNamespace::Util::ColorText::Colors::Hex::Cyan   = "#5BC0EB";
    CatedralNamespace::Util::ColorText::Colors::Hex::Green  = "#3FB950";
    CatedralNamespace::Util::ColorText::Colors::Hex::Orange = "#D29922";
    CatedralNamespace::Util::ColorText::Colors::Hex::Pink   = "#E5484D";
    CatedralNamespace::Util::ColorText::Colors::Hex::Purple = "#C13C3F";
    CatedralNamespace::Util::ColorText::Colors::Hex::Red    = "#E5484D";
    CatedralNamespace::Util::ColorText::Colors::Hex::Yellow = "#F2C94C";
}

QString CatedralNamespace::Util::ColorText::Color(const QString& color, const QString &text)
{
    return "<span style=\"color: "+ color +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Background(const QString& text)
{
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Background +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Foreground(const QString& text) {
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Foreground +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Comment(const QString& text) {
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Comment +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Cyan(const QString& text) {
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Cyan +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Green(const QString& text) {
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Green +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Orange(const QString& text) {
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Orange +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Pink(const QString& text) {
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Pink +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Purple(const QString& text) {
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Purple +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Red(const QString& text) {
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Red +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Yellow(const QString& text) {
    return "<span style=\"color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Yellow +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::Bold(const QString& text) {
    return "<b>" + text.toHtmlEscaped() + "</b>";
}

QString CatedralNamespace::Util::ColorText::Underline(const QString &text) {
    return "<span style=\"text-decoration:underline\">" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlineBackground(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Background +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlineForeground(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Foreground +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlineComment(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Comment +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlineCyan(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Cyan +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlineGreen(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Green +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlineOrange(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Orange +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlinePink(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Pink +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlinePurple(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Purple +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlineRed(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Red +";\" >" + text.toHtmlEscaped() + "</span>";
}

QString CatedralNamespace::Util::ColorText::UnderlineYellow(const QString &text) {
    return "<span style=\"text-decoration:underline; color: "+ CatedralNamespace::Util::ColorText::Colors::Hex::Yellow +";\" >" + text.toHtmlEscaped() + "</span>";
}
