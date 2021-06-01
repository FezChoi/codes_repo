package ch07;

public class DoubleTest {

	public static void main(String[] args) {
		double doubleNumber = 3.14;
		float floatNumber = 3.14F;
		
		System.out.println(doubleNumber);
		System.out.println(floatNumber);
		
		
		doubleNumber = 0;
		
		for (int i = 0; i < 10000; i++) {
			doubleNumber += 0.1;
		}
		
		System.out.println(doubleNumber);
	}

}
