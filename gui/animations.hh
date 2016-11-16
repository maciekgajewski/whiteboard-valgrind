#pragma once

#include <QObject>
#include <QMultiMap>

namespace Whiteboard {

class MemCellItem;
class Animation;

// Manages running animations
class Animations : public QObject
{
	Q_OBJECT
public:
	explicit Animations(QObject* p = nullptr);

	// advances all current animations.
	void advance(qint64 now);

	// if new animation can be added now
	bool canAddNew(qint64 now) const { return now >= blockedUntil_; }

	// if animations are running
	bool running() const { return !animations_.empty(); }

	// creating animations
	void addMemLoad(MemCellItem* cell, int size, qint64 now);
	void addMemStore(MemCellItem* cell, int size, qint64 now);

private:

	QMultiMap<qint64, Animation*> animations_; // sorted by time when they are supposed to be removed
	qint64 blockedUntil_ = 0;
};

} // namespace Whiteboard

