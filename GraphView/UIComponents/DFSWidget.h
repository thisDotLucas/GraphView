#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "../Entities/Entity.h"
#include "../Algorithms/DFSRunner.h"

class DFSWidget : public QWidget 
{
public:
    DFSWidget(QWidget* parent);

    void setStarVertex(Handle handle);

private slots:
    void onRunButton();

private:
    std::unique_ptr<DFSRunner> m_runner;
    QLineEdit* m_startVertexField;
    QPushButton* m_runButton;
};