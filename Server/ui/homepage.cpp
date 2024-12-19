#include "homepage.h"

#include <QSqlError>

#include "../objects/product.h"
#include "../dao/productmapper.h"

#include <QVBoxLayout>
#include <QChart>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPieSeries>
#include <QLegendMarker>

HomePage::HomePage(QWidget* parent)
    : BasePage(parent)
{
    setWindowTitle("首页");
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("首页");
    addCentralWidget(centralWidget, true, true, 0);
    centerLayout = new QVBoxLayout(centralWidget);
    connectToDB("HomePage");
    refreshPage();
}

HomePage::~HomePage()
{
}

void HomePage::initPage()
{
    clearPage(0);

    barChart = new QChart;
    barChart->setAnimationOptions(QChart::SeriesAnimations);
    barChart->legend()->setVisible(false);

    pieChart = new QChart;
    pieChart->setAnimationOptions(QChart::AllAnimations);
    pieChart->legend()->setVisible(true);
    pieChart->legend()->setAlignment(Qt::AlignRight);

    QChartView *barView = new QChartView(barChart, this);
    barView->setRenderHint(QPainter::Antialiasing, true);

    QChartView *pieView = new QChartView(pieChart, this);
    pieView->setRenderHint(QPainter::Antialiasing, true);

    centerLayout->addWidget(barView);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(pieView);
}

void HomePage::refreshPage()
{
    initPage();
    //建立 BarChart
    QBarSet *barSet = new QBarSet("商品销量");
    QStringList *barCategories = new QStringList;
    ProductMapper *productMapper = new ProductMapper(db);
    QList<Product *> products = productMapper->selectLike("");
    int maxSales = 0, sumSales = 0;
    for (auto product : products)
    {
        if (product->getProductId() == 0) continue;
        qDebug() << "[HomePage] insert Chart:" << product->getProductName();
        int sales = product->getProductSales();
        maxSales = maxSales < sales ? sales : maxSales;
        *barSet << sales;
        *barCategories << product->getProductName();
        sumSales += sales;
    }

    QBarSeries *barSeries = new QBarSeries;
    barSeries->append(barSet);
    barSeries->setLabelsVisible(true);
    barSeries->setLabelsFormat("@value件");
    barChart->addSeries(barSeries);
    barChart->setTitle("各商品销量对比图");

    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append(*barCategories);
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, maxSales + maxSales/10+1);
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    //创建 PieChart
    QPieSeries *pieSeries = new QPieSeries;
    for (auto product : products)
    {
        if (product->getProductId() == 0) continue;
        int sales = product->getProductSales();
        QPieSlice *pieSlice = new QPieSlice(product->getProductName(), (double)(sales)/sumSales);
        if (sales) pieSlice->setLabelVisible(true);
        pieSeries->append(pieSlice);
    }
    pieSeries->setVerticalPosition(0.55);
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("各商品销量占比图");

    QList<QLegendMarker *> markers = pieChart->legend()->markers(pieSeries);
    for (int i = 0; i < markers.count(); ++i) {
        QLegendMarker *marker = markers[i];
        QPieSlice *slice = pieSeries->slices().at(i);  // 获取对应的 QPieSlice
        marker->setLabel(slice->label() +"："+ QString::number(std::floor(slice->value()*1000)/10) + "%");  // 设置图例项显示的数值
    }
}
