#include "main_window.hh"
#include "ui_main_window.h"

#include "scene.hh"
#include "debugger.hh"
#include "source_view.hh"

#include <QTimer>

namespace Whiteboard {

MainWindow::MainWindow(QWidget *p) :
	QMainWindow(p),
	ui_(new Ui::MainWindow)
{
	ui_->setupUi(this);
	scene_ = new Scene(this);
	debugger_ = new Debugger(this);
	sourceView_ = new SourceView(this);
	sourceView_->setWindowFlags(Qt::Window);

	connect(debugger_, SIGNAL(statusChanged(const QString&)), statusBar(), SLOT(showMessage(const QString&)));
	connect(debugger_, SIGNAL(sourceLineReached(const QString&, int)), sourceView_, SLOT(showSource(const QString&, int)));
	connect(debugger_, SIGNAL(stackChange(quint64)), scene_, SLOT(onStackChange(quint64)));
	connect(debugger_, SIGNAL(memEvent(const MemEvent&)), scene_, SLOT(onMemEvent(const MemEvent&)));


	// debugger actions
	connect(ui_->actionStep_ot_next_line, SIGNAL(triggered()), debugger_, SLOT(stepInto()));
}

MainWindow::~MainWindow()
{
	delete ui_;
}

void MainWindow::openExecutable(const QString& file)
{
	QTimer::singleShot(100, [this, file]
	{
		debugger_->openExecutable(file);
		sourceView_->show();
	});
}

} // namespace Whiteboard

