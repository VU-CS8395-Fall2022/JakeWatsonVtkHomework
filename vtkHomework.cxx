#include <iostream>

#include "vtkSmartPointer.h"
#include "vtkPolyData.h"
#include "vtkXMLPolyDataReader.h"
#include "vtkPolyDataMapper.h"

#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkIntArray.h"
#include "vtkPointData.h"
#include "vtkLookupTable.h"
#include "vtkScalarBarActor.h"
#include "vtkDecimatePro.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"

#include "vtkPolyDataNormals.h"
#include "vtkArrowSource.h"
#include "vtkGlyph3D.h"

#include "vtkDistancePolyDataFilter.h"
#include "vtkCommand.h"
#include "vtkRendererCollection.h"
#include "vtkCellPicker.h"

//j
//#include "vtkScalarsToColors.h"
//#include "vtkNamedColors.h"
#include "vtkMinimalStandardRandomSequence.h"
#include "vtkFloatArray.h"

/*
int counter = 0;

class CustomMouseCallback : public vtkCommand
{
public:
  static CustomMouseCallback * New ()
  {
    CustomMouseCallback *callback = new CustomMouseCallback ;
    return callback ;
  }

  virtual void Execute (vtkObject *caller, unsigned long eventId, void *callData)
  {
    // let's find pointers to some useful structures
    vtkSmartPointer < vtkRenderWindowInteractor > interactor = dynamic_cast < vtkRenderWindowInteractor * > ( caller ) ;
    vtkSmartPointer < vtkRenderWindow > window = interactor->GetRenderWindow () ;
    vtkSmartPointer < vtkRenderer > renderer = window->GetRenderers ()->GetFirstRenderer () ;
    vtkSmartPointer < vtkCellPicker > picker = dynamic_cast < vtkCellPicker * > ( interactor->GetPicker() ) ;

    //j
    // find mouse click location
    int clickLocation[2] ;
    interactor->GetEventPosition ( clickLocation ) ;
    std::cout << "Click at: " << clickLocation[0] << " " << clickLocation[1] << std::endl ;

    // detect where the click falls on the mesh (vertex id)
    // pickedflag is 0/1, 0 means not found, 1 means something found.
    //if something is found, we get that with picker->GetpointId() a few lines later
    int pickedFlag = picker->Pick ( clickLocation[0], clickLocation[1], 0, renderer ) ;
    double pickedPos[3] ;
    picker->GetPickPosition ( pickedPos ) ;
    std::cout << "Picked: " << pickedFlag << std::endl ;
    std::cout << pickedPos[0] << " " << pickedPos[1] << " " << pickedPos[2] << std::endl;

    vtkIdType pointId = picker->GetPointId() ;
    vtkIdType cellId = picker->GetCellId () ;
    std::cout << "Point id: " << picker->GetPointId () << std::endl ;
    std::cout << "Cell id: " << picker->GetCellId () << std::endl ;
   
    // store vertex index in the scalar array
    // mesh = renderer->GetActor->GetInput() (but we don't necessarily know which of many meshes in my scene has been picked

    vtkSmartPointer < vtkPolyData > mesh = dynamic_cast < vtkPolyData * > ( picker->GetDataSet() ) ;
    if ( mesh )
      {
    vtkSmartPointer < vtkIntArray > intArray = dynamic_cast < vtkIntArray * > ( mesh->GetPointData()->GetScalars() ) ;

    // bonus: expand to local neighborhoood of the point id to make it easy to see

    // option 0: just the current vert, no neighbors
    if ( true )
      {
        intArray->SetValue ( pointId, 1.0 ) ;
	
      }

    // option 1: find the cell, find the cell's verts, change those scalars
    // we know the cell is cellId, we need to find the verts in this cell
     if ( false )
       {
         vtkSmartPointer < vtkIdList > vertList = vtkSmartPointer < vtkIdList >::New() ;
         mesh->GetCellPoints ( cellId, vertList ) ;

         for ( unsigned int i = 0 ; i < vertList->GetNumberOfIds() ; i++ )
           {
            vtkIdType currentVert = vertList->GetId ( i ) ;
	    intArray->SetValue ( currentVert, 0 ) ; //j - 1 makes green, 2 makes blue
           }
       }

    // option 2: find the vert, find the cells it's in, find all the other verts of those cells

     if ( false )
       {
         // find the vert: it's pointId
         // find the cells pointId is in
         vtkSmartPointer < vtkIdList > cellList = vtkSmartPointer < vtkIdList >::New() ;
         mesh->GetPointCells ( pointId, cellList ) ;
         // find all the verts in all cells in cellList
         for ( unsigned int c = 0 ; c < cellList->GetNumberOfIds() ; c++ )
           {
         vtkIdType currentCell = cellList->GetId ( c ) ;
         std::cout << "currentCell: " << currentCell << std::endl ;

         vtkSmartPointer < vtkIdList > vertList = vtkSmartPointer < vtkIdList >::New() ;
         mesh->GetCellPoints ( currentCell, vertList ) ;

         for ( unsigned int v = 0 ; v < vertList->GetNumberOfIds() ; v++ )
           {
             vtkIdType currentVert = vertList->GetId ( v ) ;
             std::cout << "currentVert: " << currentVert << std::endl ;
             //intArray->SetValue ( currentVert, intArray->GetValue(v) + 1 ) ;
	     //intArray->GetValue(currentVert);
	     std::cout << "intArray->GetValue(VertList->GetId(v): " << intArray->GetValue(currentVert) << std::endl;
	     //if ()
	     	     intArray->SetValue ( currentVert, intArray->GetValue(currentVert) + 1 )  ;
	     std::cout << "intArray->GetValue(VertList->GetId(v): " << intArray->GetValue(currentVert) << std::endl;

	     
	       }
	     //potentially put a loop in here for resetting values
	     //if getvalue(currentVert) > 2 (bc -1 = gray, 0 = green, 1 = white, 2 = red), then reset to 0, start over
	     //
	     //
           
           }
       }

      
     //lookupTable->ForceBuild();
      // render refresh
      mesh->Modified() ;

      }

  }
} ;

*/
class vtkTimerCallback2 : public vtkCommand
{
  public:
    int timerId;
    static vtkTimerCallback2 *New()
    {
      vtkTimerCallback2 *timerCallback = new vtkTimerCallback2;
      timerCallback->TimerCount = 5;
      return timerCallback;
    }
 
    virtual void Execute(vtkObject *caller, unsigned long eventId,
                         void * callData)
    {
      vtkSmartPointer < vtkRenderWindowInteractor > interactor = dynamic_cast < vtkRenderWindowInteractor * > ( caller ) ;
      vtkSmartPointer < vtkRenderWindow > window = interactor->GetRenderWindow () ;
      vtkSmartPointer < vtkRenderer > renderer = window->GetRenderers ()->GetFirstRenderer () ;
      vtkSmartPointer < vtkActor > actor = renderer->GetLastActor();
      vtkSmartPointer < vtkPolyDataMapper > mapper = actor->GetMapper();
      vtkSmartPointer < vtkPolyData > mesh = dynamic_cast < vtkPolyData * > ( mapper->GetInput() ) ;
      int nPoints = mesh->GetNumberOfPoints() ;

      vtkSmartPointer < vtkFloatArray > intArray = dynamic_cast < vtkFloatArray * > ( mesh->GetPointData()->GetScalars() ) ;
      vtkSmartPointer < vtkLookupTable > lookupTable = dynamic_cast < vtkLookupTable * > (mapper->GetLookupTable() ); 

      vtkSmartPointer < vtkMinimalStandardRandomSequence > random = vtkSmartPointer < vtkMinimalStandardRandomSequence >::New() ;
      random->SetSeed(1.0);
      double x = random->GetValue() * nPoints;
      int randomPoint = x;
      std::cout << "randomPoint: " << randomPoint << std::endl;
      intArray->SetValue(randomPoint, 1);
      std::cout <<"randomPoint value: " << intArray->GetValue(randomPoint) <<std::endl;
  
  
      for(unsigned int itr = 1; itr < 85 ; itr++ )
	{
	  TimerCount = TimerCount + 1;
	  // dont uncomment this// seriously dont//  std::cout << "itr1 :" << itr << std::endl;
	  for(unsigned int i = 0; i < nPoints ; i++)
	    {
	      //dont uncomment this either //std::cout << "i :" << i << std::endl;
	      vtkIdType a = intArray->GetValue(i);
	      if(a == itr)
		{
		  vtkSmartPointer <vtkIdList> cellList = vtkSmartPointer <vtkIdList>::New();
		  mesh->GetPointCells(i, cellList);
		  //mesh1->GetCellPoints(cellId, vertList)
		  for(unsigned int c = 0 ; c < cellList->GetNumberOfIds(); c++)
		    {
		      vtkIdType currentCell = cellList->GetId ( c );
		      std::cout << "currentCell :" << currentCell << std::endl;

		      vtkSmartPointer <vtkIdList> vertList = vtkSmartPointer <vtkIdList> ::New();
		      mesh->GetCellPoints(currentCell,vertList);

		      for(unsigned int v = 0; v < vertList->GetNumberOfIds(); v++)
			{
			  vtkIdType currentVert = vertList->GetId (v) ;
			  //if vert not visited
			  if(intArray->GetValue(currentVert) == 0) //0
			    {
			      //change value to current itr, which corresponds to lookupTable value(itr,r,g,b)
			      intArray->SetValue(currentVert, itr + 1);
			      std::cout << "intArray->GetValue(currentVert) = " << intArray->GetValue(currentVert) << std::endl;
			      std::cout << "itr :" << itr << std::endl;
			      std::cout << "i :" << i << std::endl;
			      std::cout << "a :" << a << std::endl;
			      std::cout << "v :" << v << std::endl;
		      
			      //mesh->Modified();
			    }
		  
			}
	      
		    }
		}
	    }
    
	  if(TimerCount % 5 == 4)
	    {
	      mesh->Modified();
	    }
	}
    }
  /*private:
    int TimerCount= 0;
  public:
    vtkActor* actor;
    int maxCount = 0;
  //timerId = 0;
  */
};

//vtkSmartPointer < vtkPolyData > DecimateMesh ( vtkSmartPointer < vtkPolyData > inputMesh )
vtkSmartPointer < vtkPolyData > DecimateMesh ( vtkSmartPointer < vtkPolyData > inputMesh, double ratio )
{
  vtkSmartPointer < vtkDecimatePro > decimateFilter = vtkSmartPointer < vtkDecimatePro >::New() ;
  decimateFilter->SetInputData ( inputMesh ) ;
  decimateFilter->SetTargetReduction ( ratio ) ;
  decimateFilter->Update () ;

  return decimateFilter->GetOutput() ;
}

int main ( int argc, char **argv )
{
  //  std::cout << "hello world - coming soon!" << std::endl ;
  //std::cout << "starting counter: " << counter << std::endl;
  if ( argc < 2 )
    {
      std::cout << "Usage: " << argv[0] << " "<< " inputFileName1" << std::endl ;
      return 0 ;
    }

  // read in the input file
  // part 1, using the lh file of the brain
  vtkSmartPointer < vtkXMLPolyDataReader > reader1 = vtkSmartPointer < vtkXMLPolyDataReader > ::New() ;
  reader1->SetFileName ( argv[1] )  ;
  reader1->Update () ;

  //vtkSmartPointer < vtkPolyData > mesh1 = DecimateMesh ( reader1->GetOutput() ) ;
  vtkSmartPointer < vtkPolyData > mesh1 = DecimateMesh ( reader1->GetOutput(), 0.90 ) ;
  //vtkSmartPointer < vtkPolyData > mesh1 = reader1->GetOutput() ;

  std::cout << "NPoints: " << reader1->GetOutput()->GetNumberOfPoints() << std::endl ;
  std::cout << "NCells: " << reader1->GetOutput()->GetNumberOfCells() << std::endl ;

  // create a vtkmapper
  vtkSmartPointer < vtkPolyDataMapper > mapper1 = vtkSmartPointer < vtkPolyDataMapper > ::New() ;

  // create an actor
    //set the color of thing brain
  vtkSmartPointer < vtkActor > actor1 = vtkSmartPointer < vtkActor >::New() ;
  actor1->SetMapper ( mapper1 ) ;
  //actor1->GetProperty()->SetColor ( 0, 0, 1 ) ;
  //actor1->GetProperty()->SetColor ( 0, 0.7, 0.4 ) ; // teal
    
   mapper1->SetInputData ( mesh1 ) ;
   //this is what sets the base color to red,
   //mapper1->ScalarVisibilityOn () ; //, or if you dont have anything
   //mapper1->ScalarVisibilityOff() ;
   //mapper1->GetScalarVisibility();
   
   // create a scalar array for the mesh that is set to -1
   // part 2
   vtkSmartPointer < vtkFloatArray > intArray = vtkSmartPointer < vtkFloatArray >::New() ;
   int nPoints = mesh1->GetNumberOfPoints() ;
   std::cout << "nPoints: " << nPoints << std::endl ;
   intArray->SetNumberOfValues ( nPoints ) ;
   mesh1->GetPointData()->SetScalars ( intArray ) ;
   for (int i = 0 ; i < nPoints ; i++ )
     {
       intArray->InsertValue(i, 0);
     }
    
   // let the visualization pipeline know about the array
   // mapper1->SetScalarModeToUsePointData() ;
    
   // we are implementing a lookuptable which is easier to manipulate
   // will change the coloration of the spots after the mouse click on the surface
   vtkSmartPointer < vtkLookupTable > lookupTable = vtkSmartPointer < vtkLookupTable >::New() ;
   //lookupTable->SetHueRange ( 0, 0.3 ) ;
   //lookupTable->SetSaturationRange ( 1, 1 )  ;
   //lookupTable->SetValueRange ( 0, 4.0 ) ;
   lookupTable->SetNumberOfTableValues(nPoints+1);
   //lookupTable->Build();
   //lookupTable->SetRange(0.0, 5.0);
   //lookupTable->SetTableRange(0.0, 4.0);
   //lookupTable->SetTableValue(-1, 0.5, 0.5, 0.5);
   lookupTable->SetTableValue(0, 0.9, 0.2, 0.2);//set initial value to red
   lookupTable->SetTableValue(1, 0.2, 0.9, 0.2);//set second value to green
   vtkSmartPointer < vtkMinimalStandardRandomSequence > randomColor = vtkSmartPointer < vtkMinimalStandardRandomSequence >::New();
   //assign lookup table values for all potential iteration values, which is 1:number of cells
   for (int lt = 2; lt < nPoints; lt++)
     {
       double r, g, b;
       r = randomColor->GetRangeValue(0.4, 0.9);
       //std::cout << "r: " << r << std::endl ; 
       randomColor->Next();
       g = randomColor->GetRangeValue(0.4, 0.9);
       //std::cout << "g: " << g << std::endl ; 
       randomColor->Next();
       b = randomColor->GetRangeValue(0.4, 0.9);
       //std::cout << "b: " << b << std::endl ; 
       randomColor->Next();
       lookupTable->SetTableValue(lt, r, g, b);
     }

   //lookupTable->SetTableValue(, 0.0, 0.9, 0.0); //set fourth to green
   // */
   //lookupTable->Build () ; // basically the update() function
   std::cout <<"# of lt values: " << lookupTable->GetNumberOfTableValues() << std::endl;
   std::cout <<"intArray value 1000 : "<<intArray->GetValue(1000) << std::endl;
   //mapper1->SetScalarModeToUsePointData() ;
   mapper1->SetScalarRange ( 0, nPoints-1 ) ; // 0 = not clicked, 1 = clicked
   mapper1->SetLookupTable ( lookupTable ) ;
   //mesh1->Modified();
   //mapper1->SetScalarVisibility(1);
  // attach the scalar array to the mesh
  

  // create a scene that keeps track of all the actors in the workspace
  vtkSmartPointer < vtkRenderer > renderer = vtkSmartPointer < vtkRenderer >::New() ;
  renderer->AddActor ( actor1 ) ;
  //set background color, christmas tree green
  renderer->SetBackground(0.1, 0.3, 0.1);
  // create a window
  vtkSmartPointer < vtkRenderWindow > window = vtkSmartPointer < vtkRenderWindow >::New() ;
  window->AddRenderer ( renderer ) ;
  window->SetSize ( 500, 500 ) ;

  // create an interactor with the window
  vtkSmartPointer < vtkRenderWindowInteractor > interactor = vtkSmartPointer < vtkRenderWindowInteractor >::New() ;
  interactor->SetRenderWindow ( window ) ;
  window->Render();
  interactor->Initialize();

  
  // create callback and add it to the interactor
  //vtkSmartPointer < CustomMouseCallback > myCallback = vtkSmartPointer < CustomMouseCallback >::New() ;
  //interactor->AddObserver ( vtkCommand::LeftButtonPressEvent , myCallback, 0);// lookupTable ) ;

  
  //vtkSmartPointer < vtkCellPicker > picker = vtkSmartPointer < vtkCellPicker >::New() ;
  //interactor->SetPicker ( picker ) ;

  
  //select a random seed to begin
  vtkSmartPointer < vtkMinimalStandardRandomSequence > random = vtkSmartPointer < vtkMinimalStandardRandomSequence >::New() ;
  random->SetSeed(1.0);
  double x = random->GetValue() * nPoints;
  int randomPoint = x;
  std::cout << "randomPoint: " << randomPoint << std::endl;
  intArray->SetValue(randomPoint, 1);
  std::cout <<"randomPoint value: " << intArray->GetValue(randomPoint) <<std::endl;
  
  
  for(unsigned int itr = 1; itr < 85 ; itr++ )
    {
      // dont uncomment this// seriously dont//  std::cout << "itr1 :" << itr << std::endl;
      for(unsigned int i = 0; i < nPoints ; i++)
       {
	 //dont uncomment this either //std::cout << "i :" << i << std::endl;
	vtkIdType a = intArray->GetValue(i);
	if(a == itr)
	  {
	   vtkSmartPointer <vtkIdList> cellList = vtkSmartPointer <vtkIdList>::New();
	   mesh1->GetPointCells(i, cellList);
           //mesh1->GetCellPoints(cellId, vertList)
	   for(unsigned int c = 0 ; c < cellList->GetNumberOfIds(); c++)
	     {
	      vtkIdType currentCell = cellList->GetId ( c );
	      std::cout << "currentCell :" << currentCell << std::endl;

	      vtkSmartPointer <vtkIdList> vertList = vtkSmartPointer <vtkIdList> ::New();
	      mesh1->GetCellPoints(currentCell,vertList);

	      for(unsigned int v = 0; v < vertList->GetNumberOfIds(); v++)
		{
                  vtkIdType currentVert = vertList->GetId (v) ;
		  //if vert not visited
		  if(intArray->GetValue(currentVert) == 0) //0
		    {
		      //change value to current itr, which corresponds to lookupTable value(itr,r,g,b)
		      intArray->SetValue(currentVert, itr + 1);
		      std::cout << "intArray->GetValue(currentVert) = " << intArray->GetValue(currentVert) << std::endl;
		      std::cout << "itr :" << itr << std::endl;
		      std::cout << "i :" << i << std::endl;
		      std::cout << "a :" << a << std::endl;
		      std::cout << "v :" << v << std::endl;
		      mesh1->Modified();
		    }
		  
		}
	      
	     }
	  }
       }
     
     
     
     mesh1->Modified();
     
    }
  
  vtkSmartPointer<vtkTimerCallback2> timerCallback = vtkSmartPointer<vtkTimerCallback2>::New();
  //timerCallback->actor = actor1;
  //timerCallback->maxCount = 5;
  int timerId = interactor->CreateTimer(100);
  timerCallback->timerId = timerId;
  interactor->AddObserver(vtkCommand::TimerEvent, timerCallback);
  //std::cout << "timerId: " << timerId << std::endl; 

  std::cout <<"The interactor starts next" << std::endl;
  interactor->Start() ;
  std::cout <<"The interactor has closed" << std::endl;
  
  return 0 ;
}
////./VtkHW ~/VU\ work/Open\ Source/Set6/lh.pial.vtp


