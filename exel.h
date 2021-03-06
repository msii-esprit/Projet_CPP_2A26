#ifndef EXEL_H
#define EXEL_H


#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QString>
class ExcelExportHelper
{
public:
    ExcelExportHelper(const ExcelExportHelper& other) = delete;
    ExcelExportHelper& operator=(const ExcelExportHelper& other) = delete;

    ExcelExportHelper(bool closeExcelOnExit = false);
    void SetCellValue(int lineIndex, int columnIndex, QString value);
    void SaveAs(const QString& fileName);

    ~ExcelExportHelper();

private:
    QAxObject* m_excelApplication;
    QAxObject* m_workbooks;
    QAxObject* m_workbook;
    QAxObject* m_sheets;
    QAxObject* m_sheet;
    bool m_closeExcelOnExit;
};

#endif // EXEL_H


