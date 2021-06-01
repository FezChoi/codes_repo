package ch20;

public class NestedLoopTeset {

	public static void main(String[] args) {

		// 구구단 for loop	
		for (int row = 1; row <= 9; row++) {
			for (int col = 1; col <= 9; col++) {
				System.out.println(row + "X" + col + "=" + row * col);
			}
			System.out.println();
		}
		
//		System.out.println();
//		System.out.println();
//
//		// 구구단 while loop
//		int row = 2;
//		while (row <= 9) {
//			
//			int col = 1;
//			while (col <= 9) {
//				
//				System.out.println(row + 'X' + col + '=' + row * col);
//				col++;
//			}
//			
//			System.out.println();
//			row++;
//		}
	}

}
