#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "../Entities/Entity.h"
#include "../Algorithms/BFSRunner.h"

class BFSWidget : public QWidget 
{
public:
    BFSWidget(QWidget* parent);

    void setStarVertex(Handle handle);

private slots:
    void onRunButton();

private:
    std::unique_ptr<BFSRunner> m_runner;
    QLineEdit* m_startVertexField;
    QPushButton* m_runButton;
};