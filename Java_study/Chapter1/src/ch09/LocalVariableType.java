package ch09;

public class LocalVariableType {

	public static void main(String[] args) {
		
		var a = 10;
		var b = 10.0;
		var c = '한';
		var d = "hello";

		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
		
		// d = 3; error!
		
	}

}
