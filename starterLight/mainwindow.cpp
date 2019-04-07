#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
/* **** début de la partie à compléter **** */

void MainWindow::showSelections(MyMesh* _mesh)
{
    // on réinitialise les couleurs de tout le maillage
    resetAllColorsAndThickness(_mesh);

    /*for(int i = 0; i <vertexSelection ; i++)
    {*/
        /*if(vertexSelection %3 == 0) //3element
        {
            _mesh->set_color(_mesh->vertex_handle(vertexSelection), MyMesh::Color(0, 0, 255));
            _mesh->data(_mesh->vertex_handle(vertexSelection)).thickness = 12;
        }
        if(vertexSelection %3 == 1 && vertexSelection>2) //2elements
        {
            _mesh->set_color(_mesh->vertex_handle(vertexSelection), MyMesh::Color(0, 0, 255));
            _mesh->set_color(_mesh->vertex_handle(vertexSelection-1), MyMesh::Color(0, 0, 255));
            _mesh->data(_mesh->vertex_handle(vertexSelection)).thickness = 12;
            _mesh->data(_mesh->vertex_handle(vertexSelection-1)).thickness = 12;
        }
        if(vertexSelection %3 == 2 && vertexSelection>3) //1element
        {
            _mesh->set_color(_mesh->vertex_handle(vertexSelection), MyMesh::Color(0, 0, 255));
            _mesh->set_color(_mesh->vertex_handle(vertexSelection-1), MyMesh::Color(0, 0, 255));
            _mesh->set_color(_mesh->vertex_handle(vertexSelection-2), MyMesh::Color(0, 0, 255));
            _mesh->data(_mesh->vertex_handle(vertexSelection)).thickness = 12;
            _mesh->data(_mesh->vertex_handle(vertexSelection-1)).thickness = 12;
            _mesh->data(_mesh->vertex_handle(vertexSelection-2)).thickness = 12;
        }*/
    //}
    /* **** à compléter ! ****
     * cette fonction utilise les vatiables de sélection vertexSelection, edgeSelection et faceSelection
     * qui sont les ID des élements sélectionnés et qui sont égales à -1 si la sélection est vide
     */
    if(vertexSelection>-1)
    {
        _mesh->set_color(_mesh->vertex_handle(vertexSelection), MyMesh::Color(0, 0, 255));
        _mesh->data(_mesh->vertex_handle(vertexSelection)).thickness = 12;
    }

    if(edgeSelection>-1)
    {
        _mesh->set_color(_mesh->edge_handle(edgeSelection), MyMesh::Color(254, 0, 0));
        _mesh->data(_mesh->edge_handle(edgeSelection)).thickness = 12;
    }

    if(faceSelection>-1)
        _mesh->set_color(_mesh->face_handle(faceSelection), MyMesh::Color(0, 0, 255));
    //_mesh->data(_mesh->face_handle(faceSelection)).;

    // on affiche le nouveau maillage
    displayMesh(_mesh);
}


void MainWindow::showSelectionsNeighborhood(MyMesh* _mesh)
{
    // on réinitialise les couleurs de tout le maillage
    resetAllColorsAndThickness(_mesh);

    /* **** à compléter ! ****
     * cette fonction utilise les vatiables de sélection vertexSelection, edgeSelection et faceSelection
     * qui sont les ID des élements sélectionnés et qui sont égales à -1 si la sélection est vide
     * et affiche en plus le voisinage de chaque sélection :
     *    - les faces voisines les faces
     *    - les faces adjacentes pour les arêtes
     *    - les arêtes incidentes pour les sommets
     */

    if(vertexSelection>-1)
    {
        float minY = _mesh->point(*(_mesh->vertices_begin()))[1];
        float maxY = minY;

        // parcours des sommets
        for (MyMesh::VertexIter curVert = _mesh->vertices_begin()+vertexSelection; curVert!=_mesh->vertices_begin()+vertexSelection+3; ++curVert)
        {
            float y = _mesh->point(*curVert)[1];
            if(minY > y) minY = y;
            if(maxY < y) maxY = y;
        }

        // on calcul le centre en Y du mesh
        float centreY = (maxY - minY) / 2.0 + minY;
        _mesh->set_color(_mesh->vertex_handle(vertexSelection), MyMesh::Color(0, 0, 255));
        _mesh->data(_mesh->vertex_handle(vertexSelection)).thickness = 12;

        for (MyMesh::FaceIter curFace = _mesh->faces_begin(); curFace != _mesh->faces_end(); curFace++)
        {
            float yMoyen = 0;
            // parcours des sommets de la face courante
            for (MyMesh::FaceVertexIter curVert = _mesh->fv_iter(*curFace); curVert.is_valid(); curVert++)
                yMoyen = yMoyen + _mesh->point(*curVert)[1];
            yMoyen = yMoyen / 3.0; // calcul du Y moyen sur la face

            // on change la couleur selon le Y moyen
            if(yMoyen > centreY)
                _mesh->set_color(*curFace, MyMesh::Color(255, 0, 0));
            else
                _mesh->set_color(*curFace, MyMesh::Color(0, 0, 255));
        }
    }

    if(edgeSelection>-1)
    {
        _mesh->set_color(_mesh->edge_handle(edgeSelection), MyMesh::Color(254, 0, 0));
        _mesh->data(_mesh->edge_handle(edgeSelection)).thickness = 12;
    }

    if(faceSelection>-1)
    {
        _mesh->set_color(_mesh->face_handle(faceSelection), MyMesh::Color(0, 0, 255));
        for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
        {
            if(_mesh->face_handle(faceSelection) == curVert)
            {
                VertexHandle vh = *curVert;
                float x = _mesh->point(vh)[0];
                float y = _mesh->point(vh)[1];
                float z = _mesh->point(vh)[2];

                //_mesh->set_color(_mesh->point(vh)[0]., MyMesh::Color(0, 0, 255));
                qDebug() << "id :" << vh.idx() << "coord :" << x << y << z;
            }

        }

    }

    // on affiche le nouveau maillage
    displayMesh(_mesh);
}



void MainWindow::showBorder(MyMesh* _mesh)
{
    // on réinitialise l'affichage
    resetAllColorsAndThickness(_mesh);

    /* **** à compléter ! **** */

    // on affiche le nouveau maillage
    displayMesh(_mesh);
}


void MainWindow::showPath(MyMesh* _mesh, int v1, int v2)
{
    // on réinitialise l'affichage
    resetAllColorsAndThickness(_mesh);

    // point de départ et point d'arrivée en vert et en gros
    _mesh->set_color(_mesh->vertex_handle(v1), MyMesh::Color(0, 255, 0));
    _mesh->set_color(_mesh->vertex_handle(v2), MyMesh::Color(0, 255, 0));
    _mesh->data(_mesh->vertex_handle(v1)).thickness = 12;
    _mesh->data(_mesh->vertex_handle(v2)).thickness = 12;

    /* **** à compléter ! **** */

    // on affiche le nouveau maillage
    displayMesh(_mesh);
}

/* **** fin de la partie à compléter **** */


/* **** début de la partie boutons et IHM **** */

void MainWindow::on_pushButton_bordure_clicked()
{
    showBorder(&mesh);
}

/*void MainWindow::on_pushButton_voisinage_clicked()
{
    // changement de mode entre avec et sans voisinage
    if(modevoisinage)
    {
        ui->pushButton_voisinage->setText("Repasser en mode normal");
        modevoisinage = false;
    }
    else
    {
        ui->pushButton_voisinage->setText("Passer en mode voisinage");
        modevoisinage = true;
    }

    // on montre la nouvelle selection
    if(!modevoisinage)
        showSelections(&mesh);
    else
        showSelectionsNeighborhood(&mesh);
}*/


void MainWindow::on_pushButton_vertexMoins_clicked()
{
    // mise à jour de l'interface
    vertexSelection = vertexSelection - 1;
    ui->labelVertex->setText(QString::number(vertexSelection));

    // on montre la nouvelle selection
    if(!modevoisinage)
        showSelections(&mesh);
    else
        showSelectionsNeighborhood(&mesh);
}

void MainWindow::on_pushButton_vertexPlus_clicked()
{
    // mise à jour de l'interface
    vertexSelection = vertexSelection + 1;
    ui->labelVertex->setText(QString::number(vertexSelection));

    // on montre la nouvelle selection
    if(!modevoisinage)
        showSelections(&mesh);
    else
        showSelectionsNeighborhood(&mesh);
}

/*void MainWindow::on_pushButton_edgeMoins_clicked()
{
    // mise à jour de l'interface
    edgeSelection = edgeSelection - 1;
    ui->labelEdge->setText(QString::number(edgeSelection));

    // on montre la nouvelle selection
    if(!modevoisinage)
        showSelections(&mesh);
    else
        showSelectionsNeighborhood(&mesh);
}*/

/*void MainWindow::on_pushButton_edgePlus_clicked()
{
    // mise à jour de l'interface
    edgeSelection = edgeSelection + 1;
    ui->labelEdge->setText(QString::number(edgeSelection));

    // on montre la nouvelle selection
    if(!modevoisinage)
        showSelections(&mesh);
    else
        showSelectionsNeighborhood(&mesh);
}*/

/*void MainWindow::on_pushButton_faceMoins_clicked()
{
    // mise à jour de l'interface
    faceSelection = faceSelection - 1;
    ui->labelFace->setText(QString::number(faceSelection));

    // on montre la nouvelle selection
    if(!modevoisinage)
        showSelections(&mesh);
    else
        showSelectionsNeighborhood(&mesh);
}*/

/*void MainWindow::on_pushButton_facePlus_clicked()
{
    // mise à jour de l'interface
    faceSelection = faceSelection + 1;
    ui->labelFace->setText(QString::number(faceSelection));

    // on montre la nouvelle selection
    if(!modevoisinage)
        showSelections(&mesh);
    else
        showSelectionsNeighborhood(&mesh);
}*/

void MainWindow::on_pushButton_afficherChemin_clicked()
{
    // on récupère les sommets de départ et d'arrivée
    int indexV1 = ui->spinBox_v1_chemin->value();
    int indexV2 = ui->spinBox_v2_chemin->value();

    showPath(&mesh, indexV1, indexV2);
}


void MainWindow::on_pushButton_chargement_clicked()
{
    // fenêtre de sélection des fichiers
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mesh"), "", tr("Mesh Files (*.obj)"));

    // chargement du fichier .obj dans la variable globale "mesh"
    OpenMesh::IO::read_mesh(mesh, fileName.toUtf8().constData());

    // initialisation des couleurs et épaisseurs (sommets et arêtes) du mesh
    resetAllColorsAndThickness(&mesh);

    // on affiche le maillage
    map_dis_pts.clear();
    map_ctrl_pts.clear();
    vectpts.clear();
    for(int i = 0; i<mesh.n_vertices();i++)
    {
        MyMesh::Point pt = mesh.point(mesh.vertex_handle(i));
        map_ctrl_pts.insert(i,pt);
        vectpts.push_back(pt);
    }
    displayMesh(&mesh);
}

/* **** fin de la partie boutons et IHM **** */



/* **** fonctions supplémentaires **** */

// permet d'initialiser les couleurs et les épaisseurs des élements du maillage
void MainWindow::resetAllColorsAndThickness(MyMesh* _mesh)
{
    for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
    {
        _mesh->data(*curVert).thickness = 1;
        _mesh->set_color(*curVert, MyMesh::Color(0, 0, 0));
    }

    for (MyMesh::FaceIter curFace = _mesh->faces_begin(); curFace != _mesh->faces_end(); curFace++)
    {
        _mesh->set_color(*curFace, MyMesh::Color(150, 150, 150));
    }

    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++)
    {
        _mesh->data(*curEdge).thickness = 1;
        _mesh->set_color(*curEdge, MyMesh::Color(0, 0, 0));
    }
}

void MainWindow::showPolyhedronOfControl(MyMesh *_mesh)
{
    /*GLuint* linesIndiceArray = new GLuint[_mesh->n_edges() * 2];
    GLfloat* linesCols = new GLfloat[_mesh->n_edges() * 2 * 3];
    GLfloat* linesVerts = new GLfloat[_mesh->n_edges() * 2 * 3];*/



    GLuint* linesIndiceArray = new GLuint;
    GLfloat* linesCols = new GLfloat;
    GLfloat* linesVerts = new GLfloat;

    int i = 0;
    QHash<float, QList<int> > edgesIDbyThickness;
    for (MyMesh::EdgeIter eit = _mesh->edges_begin(); eit != _mesh->edges_end(); ++eit)
    {
        float t = _mesh->data(*eit).thickness;
        if(t > 0)
        {
            if(!edgesIDbyThickness.contains(t))
                edgesIDbyThickness[t] = QList<int>();
            edgesIDbyThickness[t].append((*eit).idx());
        }
    }
    QHashIterator<float, QList<int> > it(edgesIDbyThickness);
    QList<QPair<float, int> > edgeSizes;
    while (it.hasNext())
    {
        it.next();

        for(int e = 0; e < it.value().size(); e++)
        {
            int eidx = it.value().at(e);

            MyMesh::VertexHandle vh1 = _mesh->to_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh1)[0];
            linesVerts[3*i+1] = _mesh->point(vh1)[1];
            linesVerts[3*i+2] = _mesh->point(vh1)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;

            MyMesh::VertexHandle vh2 = _mesh->from_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh2)[0];
            linesVerts[3*i+1] = _mesh->point(vh2)[1];
            linesVerts[3*i+2] = _mesh->point(vh2)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;
        }
        edgeSizes.append(qMakePair(it.key(), it.value().size()));
    }

    ui->displayWidget->loadLines(linesVerts, linesCols, i * 3, linesIndiceArray, i, edgeSizes);

    delete[] linesIndiceArray;
    delete[] linesCols;
    delete[] linesVerts;
}



// charge un objet MyMesh dans l'environnement OpenGL
void MainWindow::displayMesh(MyMesh* _mesh)
{
    qDebug() << __FUNCTION__;

    int i = 0;

    // ------------------------------------------------ Faces --------------------------------------
    /*GLuint* triIndiceArray = new GLuint[_mesh->n_faces() * 3];
    GLfloat* triCols = new GLfloat[_mesh->n_faces() * 3 * 3];
    GLfloat* triVerts = new GLfloat[_mesh->n_faces() * 3 * 3];

    MyMesh::ConstFaceIter fIt(_mesh->faces_begin()), fEnd(_mesh->faces_end());
    MyMesh::ConstFaceVertexIter fvIt;
    i = 0;
    for (; fIt!=fEnd; ++fIt)
    {
        fvIt = _mesh->cfv_iter(*fIt);
        triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
        triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
        triIndiceArray[i] = i;

        i++; ++fvIt;
        triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
        triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
        triIndiceArray[i] = i;

        i++; ++fvIt;
        triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
        triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
        triIndiceArray[i] = i;

        i++;
    }

    ui->displayWidget->loadMesh(triVerts, triCols, _mesh->n_faces() * 3 * 3, triIndiceArray, _mesh->n_faces() * 3);

    delete[] triIndiceArray;
    delete[] triCols;
    delete[] triVerts;*/

    // ------------------------------------------------ Edges --------------------------------------
    GLuint* linesIndiceArray = new GLuint[_mesh->n_edges() * 2];
    GLfloat* linesCols = new GLfloat[_mesh->n_edges() * 2 * 3];
    GLfloat* linesVerts = new GLfloat[_mesh->n_edges() * 2 * 3];

    i = 0;
    QHash<float, QList<int> > edgesIDbyThickness;
    for (MyMesh::EdgeIter eit = _mesh->edges_begin(); eit != _mesh->edges_end(); ++eit)
    {
        float t = _mesh->data(*eit).thickness;
        if(t > 0)
        {
            if(!edgesIDbyThickness.contains(t))
                edgesIDbyThickness[t] = QList<int>();
            edgesIDbyThickness[t].append((*eit).idx());
        }
    }
    QHashIterator<float, QList<int> > it(edgesIDbyThickness);
    QList<QPair<float, int> > edgeSizes;
    while (it.hasNext())
    {
        it.next();

        for(int e = 0; e < it.value().size(); e++)
        {
            int eidx = it.value().at(e);

            MyMesh::VertexHandle vh1 = _mesh->to_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh1)[0];
            linesVerts[3*i+1] = _mesh->point(vh1)[1];
            linesVerts[3*i+2] = _mesh->point(vh1)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;

            MyMesh::VertexHandle vh2 = _mesh->from_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh2)[0];
            linesVerts[3*i+1] = _mesh->point(vh2)[1];
            linesVerts[3*i+2] = _mesh->point(vh2)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;
        }
        edgeSizes.append(qMakePair(it.key(), it.value().size()));
    }

    ui->displayWidget->loadLines(linesVerts, linesCols, i * 3, linesIndiceArray, i, edgeSizes);

    delete[] linesIndiceArray;
    delete[] linesCols;
    delete[] linesVerts;

    // ------------------------------------------------ Vertices --------------------------------------
    GLuint* pointsIndiceArray = new GLuint[_mesh->n_vertices()];
    GLfloat* pointsCols = new GLfloat[_mesh->n_vertices() * 3];
    GLfloat* pointsVerts = new GLfloat[_mesh->n_vertices() * 3];

    i = 0;
    QHash<float, QList<int> > vertsIDbyThickness;
    for (MyMesh::VertexIter vit = _mesh->vertices_begin(); vit != _mesh->vertices_end(); ++vit)
    {
        float t = _mesh->data(*vit).thickness;
        if(t > 0)
        {
            if(!vertsIDbyThickness.contains(t))
                vertsIDbyThickness[t] = QList<int>();
            vertsIDbyThickness[t].append((*vit).idx());
        }
    }
    QHashIterator<float, QList<int> > vitt(vertsIDbyThickness);
    QList<QPair<float, int> > vertsSizes;

    while (vitt.hasNext())
    {
        vitt.next();

        for(int v = 0; v < vitt.value().size(); v++)
        {
            int vidx = vitt.value().at(v);

            pointsVerts[3*i+0] = _mesh->point(_mesh->vertex_handle(vidx))[0];
            pointsVerts[3*i+1] = _mesh->point(_mesh->vertex_handle(vidx))[1];
            pointsVerts[3*i+2] = _mesh->point(_mesh->vertex_handle(vidx))[2];
            pointsCols[3*i+0] = _mesh->color(_mesh->vertex_handle(vidx))[0];
            pointsCols[3*i+1] = _mesh->color(_mesh->vertex_handle(vidx))[1];
            pointsCols[3*i+2] = _mesh->color(_mesh->vertex_handle(vidx))[2];
            pointsIndiceArray[i] = i;
            i++;
        }
        vertsSizes.append(qMakePair(vitt.key(), vitt.value().size()));
    }

    ui->displayWidget->loadPoints(pointsVerts, pointsCols, i * 3, pointsIndiceArray, i, vertsSizes);

    delete[] pointsIndiceArray;
    delete[] pointsCols;
    delete[] pointsVerts;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    vertexSelection = -1;
    edgeSelection = -1;
    faceSelection = -1;

    modevoisinage = false;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBern(MyMesh * _mesh)
{
    for(int i = 0 ;i<vectpts.size();i++)
    {
        _mesh->add_vertex(vectpts.at(i));
    }
    displayMesh(_mesh);
}



void MainWindow::on_addControlPointButton_clicked()
{
    resetAllColorsAndThickness(&mesh);
    MyMesh * _mesh = &mesh;
    //qDebug() << _mesh->n_vertices();
    //resetAllColorsAndThickness(_mesh);
    GLfloat pointCoords[3] =
        {static_cast<GLfloat>(ui->coordXSpinBox->value()),
         static_cast<GLfloat>(ui->coordYSpinBox->value()),
         static_cast<GLfloat>(ui->coordZSpinBox->value())};
    MyMesh::Point pt = MyMesh::Point(pointCoords);
    int idx = _mesh->add_vertex(pt).idx();
    //mesh.add_vertex(pt);
    map_ctrl_pts.insert(idx,pt);

    vectpts.push_back(MyMesh::Point(pointCoords));
    //vectpts.push_back(MyMesh::Point(pointCoords));
    //drawBern(_mesh);
    //_mesh->set_color(_mesh->vertex_handle(0), MyMesh::Color(0, 0, 255));
    //_mesh->data(_mesh->vertex_handle(0)).thickness = 12;
    if (_mesh->n_vertices() > 2) {
        qDebug() << __FUNCTION__ << " in if condition";
        std::vector<MyMesh::VertexHandle > vector_vertex_for_face_handle;
        //vector_vertex_for_face_handle->clear();
        /*vector_vertex_for_face_handle.push_back(_mesh->vertex_handle(static_cast<unsigned int>(_mesh->n_vertices()-3)));
        vector_vertex_for_face_handle.push_back(_mesh->vertex_handle(static_cast<unsigned int>(_mesh->n_vertices()-2)));
        vector_vertex_for_face_handle.push_back(_mesh->vertex_handle(static_cast<unsigned int>(_mesh->n_vertices()-1)));*/
        /*for(int i = 0;i<_mesh->n_vertices();i++)
        {
            vector_vertex_for_face_handle.push_back(_mesh->vertex_handle(i));


        }*/

    }

    setColors(_mesh);

    displayMesh(_mesh);
    qDebug() << _mesh->n_vertices();


}

void MainWindow::on_clear_button_clicked()
{
    MyMesh * _mesh = &mesh;
    _mesh->clear();
    map_dis_pts.clear();
    map_ctrl_pts.clear();
    vectpts.clear();
    resetAllColorsAndThickness(&mesh);
    displayMesh(_mesh);
}
void MainWindow::setColors(MyMesh * _mesh)
{
    if(!map_ctrl_pts.isEmpty())
    {
        foreach(MyMesh::Point pt, map_ctrl_pts)
        {
            _mesh->set_color(_mesh->vertex_handle(map_ctrl_pts.key(pt)), MyMesh::Color(0, 255, 0));

            _mesh->data(_mesh->vertex_handle(map_ctrl_pts.key(pt))).thickness = 12;
        }
        if(vertexSelection>-1 && vertexSelection<map_ctrl_pts.size())
            _mesh->set_color(_mesh->vertex_handle(vertexSelection), MyMesh::Color(255, 0, 0));
    }
    if(!map_dis_pts.isEmpty())
    {
        foreach(MyMesh::Point pt, map_dis_pts)
        {
            _mesh->set_color(_mesh->vertex_handle(map_dis_pts.key(pt)), MyMesh::Color(0, 0, 255));
            _mesh->data(_mesh->vertex_handle(map_dis_pts.key(pt))).thickness = 6;
        }
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    MyMesh * _mesh = &mesh;
    resetAllColorsAndThickness(&mesh);
    if(event->key() == Qt::Key_W)
    {
        if(vertexSelection>0)
            vertexSelection = vertexSelection -1;
        else
            vertexSelection = map_ctrl_pts.size()-1;

    }
    if(event->key() == Qt::Key_X)
    {
        vertexSelection = (vertexSelection +1) % (map_ctrl_pts.size());
        qDebug()<<"map_ctrl_pts size : "<< map_ctrl_pts.size();
        qDebug()<<"vertexSelection : "<<vertexSelection;
    }

    if(event->key() == Qt::Key_Q)
    {
        foreach(MyMesh::Point pt, map_ctrl_pts)
        {
            if(map_ctrl_pts.key(pt) == vertexSelection)
            {
                MyMesh::Point point = pt;
                point[0]-=0.1;
                qDebug()<<"On Q pressed : "<<pt[0];
                map_ctrl_pts.remove(vertexSelection);
                map_ctrl_pts.insert(vertexSelection,point);
                refreshCtrlPts(_mesh);
            }
        }
    }

    if(event->key() == Qt::Key_D)
    {
        foreach(MyMesh::Point pt, map_ctrl_pts)
        {
            if(map_ctrl_pts.key(pt) == vertexSelection)
            {
                MyMesh::Point point = pt;
                point[0]+=0.1;
                qDebug()<<"On Q pressed : "<<pt[0];
                map_ctrl_pts.remove(vertexSelection);
                map_ctrl_pts.insert(vertexSelection,point);
                refreshCtrlPts(_mesh);
            }
        }
    }
    if(event->key() == Qt::Key_S)
    {
        foreach(MyMesh::Point pt, map_ctrl_pts)
        {
            if(map_ctrl_pts.key(pt) == vertexSelection)
            {
                MyMesh::Point point = pt;
                point[1]-=0.1;
                qDebug()<<"On Q pressed : "<<pt[0];
                map_ctrl_pts.remove(vertexSelection);
                map_ctrl_pts.insert(vertexSelection,point);
                refreshCtrlPts(_mesh);
            }
        }
    }
    if(event->key() == Qt::Key_Z)
    {
        foreach(MyMesh::Point pt, map_ctrl_pts)
        {
            if(map_ctrl_pts.key(pt) == vertexSelection)
            {
                MyMesh::Point point = pt;
                point[1]+=0.1;
                qDebug()<<"On Q pressed : "<<pt[0];
                map_ctrl_pts.remove(vertexSelection);
                map_ctrl_pts.insert(vertexSelection,point);
                refreshCtrlPts(_mesh);
            }
        }
    }
    if(event->key() == Qt::Key_A)
    {
        foreach(MyMesh::Point pt, map_ctrl_pts)
        {
            if(map_ctrl_pts.key(pt) == vertexSelection)
            {
                MyMesh::Point point = pt;
                point[2]-=0.1;
                qDebug()<<"On Q pressed : "<<pt[0];
                map_ctrl_pts.remove(vertexSelection);
                map_ctrl_pts.insert(vertexSelection,point);
                refreshCtrlPts(_mesh);
            }
        }
    }
    if(event->key() == Qt::Key_E)
    {
        foreach(MyMesh::Point pt, map_ctrl_pts)
        {
            if(map_ctrl_pts.key(pt) == vertexSelection)
            {
                MyMesh::Point point = pt;
                point[2]+=0.1;
                qDebug()<<"On Q pressed : "<<pt[0];
                map_ctrl_pts.remove(vertexSelection);
                map_ctrl_pts.insert(vertexSelection,point);
                refreshCtrlPts(_mesh);
            }
        }
    }
    setColors(_mesh);
    displayMesh(_mesh);
}
MyMesh::Point MainWindow::discretisation(MyMesh *_mesh,float t,float dt, int i)
{
    MyMesh::Point pt = pow(1 -t,3)*vectpts.at(i)
            + 3*t*pow(1-t,2)*vectpts.at(i+1)
            + 3*pow(t,2)*(1-t)*vectpts.at(i+2)
            + pow(t,3)*vectpts.at(i+3);
    return pt;
   /* while(t<1)
    {
        if(discretisation())
        {
            dt = t/2;
        }
        else if()
        {
            dt = dt + dt/2;
        }
        else
        {
            t = t+ dt;
        }
    }*/
}

void MainWindow::refreshCtrlPts(MyMesh *_mesh)
{
    map_dis_pts.clear();
    _mesh->clear();
    int i = 0;
    foreach(MyMesh::Point pt, map_ctrl_pts)
    {
        int idx = _mesh->add_vertex(pt).idx();
        vectpts[vertexSelection] = pt;
    }

    //setColors(_mesh);

    //displayMesh(_mesh);
}

int fact(int n)
{
    if(n <=1)
    {
        return 1;
    }
    else
        return n*fact(n-1);
}
//problème factorielle repasser dessus
void MainWindow::on_draw_button_clicked()
{
    MyMesh * _mesh = &mesh;
    refresh(_mesh);
    //resetAllColorsAndThickness(&mesh);
    float t = 0;
    float dt = 0;
    //float rangemin;
    //float rangemax;

    //int n = 10;
    //int m = vectpts.size();

    int n = sqrt(vectpts.size());
    int m = sqrt(vectpts.size());
    /*
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m - 3; j++)
        {
            MyMesh::Point pt = discretisation(_mesh,t,n,j);
            map_dis_pts.insert(_mesh->add_vertex(pt).idx(),pt);
            t = t + 1.0/ n;
        }
    }
    */
    //MyMesh::Point point = vectpts[0];

    float u = 0.0;
    for (int h=0;h<pas_u;h++)
    {
        float v = 0.0;

        for(int p=0; p<pas_v;p++)
        {

            MyMesh::Point point = vectpts[0];
            for(int i=0;i<3;++i)
            {
                float temp = 0.0;

                for (int j = 0; j < n; ++j)
                {

                    for (int k = 0; k < m; ++k)
                    {
                        /*MyMesh::Point pt = discretisation(_mesh,u,n,j)*discretisation(_mesh,v,n,j);
                        map_dis_pts.insert(_mesh->add_vertex(pt).idx(),pt);

                        t = t + 1.0/ n;
                        //u = t;*/


                        /*temp += static_cast <float>(((static_cast <float>(fact(n-1.0)))/
                                                     (static_cast <float>(fact(i))*
                                                                  static_cast <float>(fact(n-1.0-i))))
                                *static_cast <float>(pow(u,i))*
                                static_cast <float>(pow(1.0-u,(n-1.0-i)))
                                *(static_cast <float>(fact(m-1.0))
                                                            /(static_cast <float>(fact(j))
                                                              *static_cast <float>(fact(m-1.0-j))))
                                *static_cast <float>(pow(v,j))*
                                static_cast <float>(pow(1.0-v,(m-1.0-j))))*vectpts.at(i*2+j)[k];*/
                                qDebug()<<"temp : "<<temp;
                                qDebug()<<"vector "<<k<<" :"<<vectpts.at(j*2+k)[i];
                                temp += (fact(n-1)/
                                         (fact(j)*fact(n-1-j)))
                                        *pow(u,j)*pow(1-u,(n-1-j))*
                                        (fact(m-1)/
                                         (fact(k)*fact(m-1-k)))*pow(v,k)*
                                        pow(1-v,(m-1-k))*vectpts.at(j*m+k)[i];
                    }
                }
                point[i] =  temp;
            }
            map_dis_pts.insert(_mesh->add_vertex(point).idx(),point);

            v = v + 1.0/pas_v;
        }
        u = u + 1.0/pas_u;

    }



    setColors(_mesh);

    displayMesh(_mesh);
}

void MainWindow::on_u_slider_sliderMoved(int position)
{
    pas_u = static_cast<float> (position);
    on_draw_button_clicked();
}

void MainWindow::on_v_slider_sliderMoved(int position)
{
    pas_v = static_cast<float> (position);
    on_draw_button_clicked();
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,tr("Save OBJ"),QDir::homePath(), "OBJ (*.obj)");
    path +=".obj";
    QFile file(path);

    if(!file.open(QIODevice::WriteOnly |QIODevice::Text))
        return;
    QTextStream data(&file);
    data.setCodec("UTF-8");
    data<<"g"<<endl;
    foreach(MyMesh::Point pt, map_ctrl_pts)
    {
        data<<"v "<<pt[0]<<" "<<pt[1]<<" "<<pt[2]<<endl;
    }

}

void MainWindow::on_hide_button_clicked()
{
    MyMesh * _mesh = &mesh;
    foreach(MyMesh::Point pt, map_ctrl_pts)
    {
        _mesh->set_color(_mesh->vertex_handle(map_ctrl_pts.key(pt)), MyMesh::Color(0, 0, 255));
        _mesh->data(_mesh->vertex_handle(map_ctrl_pts.key(pt))).thickness = 0;
    }
    displayMesh(_mesh);
}
