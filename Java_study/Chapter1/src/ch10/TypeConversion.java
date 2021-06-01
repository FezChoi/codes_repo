package ch10;

public class TypeConversion {

	public static void main(String[] args) {
		
		double doubleNumber = 1.2;
		float floatNumber = 0.9F;
		
		int intNumber;
		
		// floor to integer
		intNumber = (int)doubleNumber + (int)floatNumber;
		System.out.println(intNumber);
		
		// round to integer
		intNumber = (int)(doubleNumber + floatNumber);
		System.out.println(intNumber);
	}

}
