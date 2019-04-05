#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <QMap>
#include <QKeyEvent>
namespace Ui {
class MainWindow;
}

using namespace OpenMesh;
using namespace OpenMesh::Attributes;

struct MyTraits : public OpenMesh::DefaultTraits
{
    // use vertex normals and vertex colors
    VertexAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color );
    // store the previous halfedge
    HalfedgeAttributes( OpenMesh::Attributes::PrevHalfedge );
    // use face normals face colors
    FaceAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color );
    EdgeAttributes( OpenMesh::Attributes::Color );
    // vertex thickness
    VertexTraits{float thickness;};
    // edge thickness
    EdgeTraits{float thickness;};
};
typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits> MyMesh;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // les 4 fonctions à compléter
    void showSelections(MyMesh* _mesh);
    void showSelectionsNeighborhood(MyMesh* _mesh);
    void showPath(MyMesh* _mesh, int v1, int v2);
    void showBorder(MyMesh* _mesh);

    void displayMesh(MyMesh *_mesh);
    void resetAllColorsAndThickness(MyMesh* _mesh);

    // ---
    void showPolyhedronOfControl(MyMesh * _mesh);
    void drawBern(MyMesh * _mesh);
    MyMesh::Point discretisation(MyMesh * _mesh,float t,float dt, int i);
    void polynomB();
    void refreshCtrlPts(MyMesh * _mesh);
    void setColors(MyMesh * _mesh);
    inline void refresh(MyMesh * _mesh)
    {
        resetAllColorsAndThickness(&mesh);
        _mesh->clear();
        /*foreach(MyMesh::Point pt,map_dis_pts)
        {
            if(_mesh->vertex_handle(map_dis_pts.key(pt)).is_valid())
                _mesh->delete_vertex(_mesh->vertex_handle(map_dis_pts.key(pt)));
        }*/
        map_dis_pts.clear();
        foreach(MyMesh::Point pt,map_ctrl_pts)
        {
            _mesh->add_vertex(pt);
        }

        //setColors(_mesh);
        //displayMesh(_mesh);
    };
    void keyPressEvent(QKeyEvent * event);
private slots:

    void on_pushButton_chargement_clicked();
    void on_pushButton_vertexMoins_clicked();
    void on_pushButton_vertexPlus_clicked();
    void on_pushButton_edgeMoins_clicked();
    void on_pushButton_edgePlus_clicked();
    void on_pushButton_faceMoins_clicked();
    void on_pushButton_facePlus_clicked();
    void on_pushButton_afficherChemin_clicked();
    void on_pushButton_voisinage_clicked();
    void on_pushButton_bordure_clicked();

    void on_addControlPointButton_clicked();

    void on_clear_button_clicked();

    void on_draw_button_clicked();

    void on_u_slider_sliderMoved(int position);

    void on_v_slider_sliderMoved(int position);

    void on_pushButton_clicked();

private:

    bool modevoisinage;
    QVector <MyMesh::Point> vectpts;

    QMap <int, MyMesh::Point> map_ctrl_pts;
    QMap <int, MyMesh::Point> map_dis_pts;
    MyMesh mesh;

    int vertexSelection;
    int edgeSelection;
    int faceSelection;

    int largeur = 0;
    int profondeur = 0;

    float pas_u = 5.0;
    float pas_v = 5.0;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
