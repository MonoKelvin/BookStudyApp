#ifndef PROMPTWIDGET_H
#define PROMPTWIDGET_H

#include <QLabel>

class PromptWidget : public QWidget
{
    Q_OBJECT
public:
    PromptWidget(const QString &prompt, QWidget *parent);

    enum class PromptType
    {
        Alert,
        Prompt
    };

    void show(PromptType type = PromptType::Prompt);
};

#endif // PROMPTWIDGET_H
