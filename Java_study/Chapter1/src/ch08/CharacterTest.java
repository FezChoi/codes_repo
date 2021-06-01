package ch08;

public class CharacterTest {

	public static void main(String[] args) {
		
		char c1 = 'A';
		System.out.println(c1);
		System.out.println((int)c1);
		
		char c2 = 66;
		System.out.println(c2);
		System.out.println((char)c2);
		
		char c3 = '한';
		char c4 = '\uD55C'; // check hangeul-unicode table
		System.out.println(c3);
		System.out.println(c4);
	}

}
