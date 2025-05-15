#ifndef TABLECOMPONENT_H
#define TABLECOMPONENT_H

#include <QTableView>
#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

// 产品类：完整的表格组件（含模型、视图、代理）
class TableComponent {
public:
    QTableView* view() const { return m_view; }
    QAbstractTableModel* model() const { return m_model; }
    QStyledItemDelegate* delegate() const { return m_delegate; }

    // 添加公共的setter方法
    void setView(QTableView* view) { m_view = view; }
    void setModel(QAbstractTableModel* model) { m_model = model; }
    void setDelegate(QStyledItemDelegate* delegate) { m_delegate = delegate; }
private:
    QTableView* m_view = nullptr;
    QAbstractTableModel* m_model = nullptr;
    QStyledItemDelegate* m_delegate = nullptr;
};

// 抽象建造者：定义表格组件的构建步骤
class AbstractTableBuilder {
public:
    virtual ~AbstractTableBuilder() = default;
    virtual void buildView(QWidget* parent) = 0;       // 构建视图
    virtual void buildModel(const QList<QVariantList>& data) = 0; // 构建模型（传入数据）
    virtual void buildDelegate() = 0;                  // 构建代理
    virtual TableComponent getResult() = 0;            // 获取最终组件
};

// 具体建造者：财务表格建造者（支持金额格式化）
class FinanceTableBuilder : public AbstractTableBuilder {
public:
    void buildView(QWidget* parent) override {
        QTableView* view = new QTableView(parent);
        view->setAlternatingRowColors(true);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        // 添加此行启用双击编辑
        view->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
        m_component.setView(view); // 使用setter设置视图
    }

    void buildModel(const QList<QVariantList>& data) override {
        // 自定义模型：支持金额列格式化（如 1000 → ¥1,000.00）
        FinanceModel* model = new FinanceModel(data, m_component.view());
        m_component.setModel(model); // 使用setter设置模型
        m_component.view()->setModel(model); // 关键：将模型设置到视图
    }

    void buildDelegate() override {
        // 自定义代理：限制金额输入格式
        CurrencyDelegate* delegate = new CurrencyDelegate(m_component.view());
        m_component.setDelegate(delegate); // 使用setter设置代理
        m_component.view()->setItemDelegate(delegate);
    }

    TableComponent getResult() override { return m_component; }

private:
    TableComponent m_component;

    // 内部类：财务模型（继承自 QAbstractTableModel）
    class FinanceModel : public QAbstractTableModel {
    public:
        FinanceModel(const QList<QVariantList>& data, QObject* parent = nullptr)
            : QAbstractTableModel(parent), m_data(data) {}

        int rowCount(const QModelIndex& = QModelIndex()) const override { return m_data.size(); }
        int columnCount(const QModelIndex& = QModelIndex()) const override {
            return m_data.isEmpty() ? 0 : m_data.first().size();
        }

        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
            if (!index.isValid() || role != Qt::DisplayRole) return {};
            const auto& row = m_data[index.row()];
            if (index.column() == 2) { // 假设第三列是金额
                double value = row[index.column()].toDouble();
                return QString("¥%L1.02f").arg(value, 0, 'f', 2); // 格式化金额
            }
            return row[index.column()];
        }

        Qt::ItemFlags flags(const QModelIndex &index) const override {
            return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
        }

        // 在FinanceModel中添加数据修改支持
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override {
            if (!index.isValid() || role != Qt::EditRole) return false;

            // 处理金额列的特殊转换
            if (index.column() == 2) {
                bool ok;
                double num = value.toDouble(&ok);
                if (!ok) return false;
                m_data[index.row()][index.column()] = num;
            } else {
                m_data[index.row()][index.column()] = value;
            }

            emit dataChanged(index, index);
            return true;
        }

    private:
        QList<QVariantList> m_data;
    };

    // 内部类：货币代理（限制输入格式）
    class CurrencyDelegate : public QStyledItemDelegate {
    public:
        using QStyledItemDelegate::QStyledItemDelegate;  // 继承构造函数
        QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override
        {
            // 仅在金额列（第3列）使用自定义编辑器
            if (index.column() != 2) {
                return QStyledItemDelegate::createEditor(parent, option, index);
            }

            QLineEdit* editor = new QLineEdit(parent);
            QRegularExpressionValidator* validator = new QRegularExpressionValidator(
                QRegularExpression("^-?\\d{1,3}(,\\d{3})*(\\.\\d{1,2})?$"),
                editor
                );
            editor->setValidator(validator);
            return editor;
        }

        void setModelData(QWidget* editor, QAbstractItemModel* model,
                          const QModelIndex& index) const override
        {
            if (index.column() != 2) { // 仅处理金额列
                QStyledItemDelegate::setModelData(editor, model, index);
                return;
            }

            QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
            if (lineEdit) {
                QString value = lineEdit->text().replace(",", ""); // 移除千位分隔符
                bool ok;
                double num = value.toDouble(&ok);
                if (ok) {
                    model->setData(index, num);
                }
            }
        }

        void paint(QPainter* painter, const QStyleOptionViewItem& option,
                   const QModelIndex& index) const override
        {
            if (index.column() == 2) {
                double value = index.data(Qt::EditRole).toDouble();
                QString text = QString("¥%L1").arg(value, 0, 'f', 2);
                QStyleOptionViewItem localOption = option;
                initStyleOption(&localOption, index);
                localOption.text = text;
                QStyledItemDelegate::paint(painter, localOption, index);
            } else {
                QStyledItemDelegate::paint(painter, option, index);
            }
        }
    };
};

// 指挥者：控制表格构建流程
class TableDirector {
public:
    explicit TableDirector(AbstractTableBuilder* builder) : m_builder(builder) {}

    void construct(QWidget* parent, const QList<QVariantList>& data) {
        m_builder->buildView(parent);  // 先构建视图（需要父组件）
        m_builder->buildModel(data);   // 再构建模型（依赖视图的父对象）
        m_builder->buildDelegate();    // 最后构建代理（依赖视图）
    }

private:
    AbstractTableBuilder* m_builder;
};

// 使用示例
void createFinanceTable(QWidget* parent) {
    // 模拟财务数据（行→列：日期、项目、金额）
    QList<QVariantList> data = {
        {"2024-01-01", "收入", 15000.00},
        {"2024-01-02", "支出", -2300.50},
        {"2024-01-03", "收入", 8000.00}
    };

    // 使用财务表格建造者
    FinanceTableBuilder builder;
    TableDirector director(&builder);
    director.construct(parent, data);

    // 获取并显示表格
    TableComponent component = builder.getResult();

    // 获取并显示表格（关键修改：使用父部件现有布局）
    if (parent->layout()) {
        parent->layout()->addWidget(component.view());
    } else {
        QVBoxLayout* layout = new QVBoxLayout(parent);
        layout->addWidget(component.view());
    }
}

#endif // TABLECOMPONENT_H
