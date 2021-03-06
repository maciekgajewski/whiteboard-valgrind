#pragma once

#include <QWidget>

namespace Whiteboard {

namespace Ui {
class SourceView;
}

class SourceView : public QWidget
{
	Q_OBJECT

public:
	explicit SourceView(QWidget* p = nullptr);
	~SourceView();

public slots:

	void showSource(const QString& file, int line);

protected:

	void closeEvent(QCloseEvent* e) override;

private:
	Ui::SourceView* ui_;
};


} // namespace Whiteboard
