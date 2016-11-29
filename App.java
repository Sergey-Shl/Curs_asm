import java.util.ArrayList;
import java.util.Random;

import javax.lang.model.element.QualifiedNameable;
import javax.swing.plaf.SliderUI;

public class Application {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int numOfInt = 50000000;
		int numOfThreads = 4;
		
		qSort q = new qSort(numOfInt);
		
		q.quickSortT(numOfInt, numOfThreads);
		
		//q.quickSort(0, 5);
		//q.finalSortNew(0, 4, -1);
		//q.print();
	}

}
