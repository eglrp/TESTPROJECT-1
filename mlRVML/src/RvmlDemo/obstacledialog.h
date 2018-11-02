#ifndef OBSTACLEDIALOG_H
#define OBSTACLEDIALOG_H

#include <QDialog>
#include<qfiledialog.h>
namespace Ui {
    class ObstacleDialog;
}

class ObstacleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ObstacleDialog(QWidget *parent = 0);
    ~ObstacleDialog();
    QString srcfilename;
    QString dstfilename;
    int nWindowSize;
    double zfactor;

    // �¶ȶ��ϰ�ͼ��ϵ��
    double dSlopeCoef;
    //����¶����� dSlopCoef * SlopeValue / dMaxSlope Ϊ�ϰ����ۺ�������ֵ����������
    double dMaxSlope;
    // �ֲڶ�ϵ��
    double dRoughnessCoef;
    // ���ֲڶ�����
    double dMaxRoughness;
    // ����ϵ��
    double dStepCoef;
    // ������ϵ��
    double dMaxStep;
    // ����ϰ���������,�ϰ����ۺ���������ֵ����֮Ϊ�ϰ�
    double dMaxObstacleValue;

private slots:
    void on_pushButtonSource_clicked();

    void on_pushButtonDest_clicked();

    void on_lineEditSource_textChanged(QString );

    void on_lineEditDest_textChanged(QString );

    void on_doubleSpinBoxWindowSize_valueChanged(double );

    void on_doubleSpinBoxZfactor_valueChanged(double );

    void on_ObstacleDialog_accepted();

    void on_doubleSpinBoxSlope_valueChanged(double );

    void on_doubleSpinBoxSlopeCoef_valueChanged(double );

    void on_doubleSpinBoxRoughness_valueChanged(double );

    void on_doubleSpinBoxRoughnessCoef_valueChanged(double );

    void on_doubleSpinBoxStep_valueChanged(double );

    void on_doubleSpinBoxStepCoef_valueChanged(double );

    void on_doubleSpinBoxObstacleValue_valueChanged(double );

    void on_buttonBox_accepted();

private:
    Ui::ObstacleDialog *ui;
};

#endif // OBSTACLEDIALOG_H
