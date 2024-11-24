#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "../Entities/Entity.h"
#include "../Algorithms/DijkstraRunner.h"

class DijkstraWidget : public QWidget 
{
public:
    DijkstraWidget(QWidget* parent);

    void setVertex(Handle handle);

private slots:
    void onRunButton();

private:
    std::unique_ptr<DijkstraRunner> m_runner;
    QLineEdit* m_startVertexField;
    QLineEdit* m_toVertexField;
    QPushButton* m_runButton;
};