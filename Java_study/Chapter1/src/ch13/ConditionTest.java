package ch13;

import java.util.Scanner;

public class ConditionTest {

	public static void main(String[] args) {
		
		System.out.println("입력 받은 두 숫자 중 큰 수를 출력하세요.\n");
		
		Scanner scanner = new Scanner(System.in);
		
		System.out.println("숫자 1 : ");
		int number1 = scanner.nextInt();
		
		System.out.println("숫자 2 : ");
		int number2 = scanner.nextInt();
				
		System.out.println((number1 > number2) ? number1 : number2);
	}

}
