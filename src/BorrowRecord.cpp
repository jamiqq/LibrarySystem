#include <BorrowRecord.h>

BorrowRecord::BorrowRecord(int itemId, int memberId)
        : itemId(itemId), memberId(memberId), borrowDate(), dueDate(borrowDate.addDays(7)), returned(false) {}

BorrowRecord::~BorrowRecord() {}

bool BorrowRecord::checkIsReturned() const{
    return returned;
}