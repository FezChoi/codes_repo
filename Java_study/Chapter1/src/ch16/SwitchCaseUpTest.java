package ch16;

import java.util.Scanner;

public class SwitchCaseUpTest {

	public static void main(String[] args) {
		
		Scanner scanner = new Scanner(System.in);

		System.out.println("월을 입력하세요.");
		int month = scanner.nextInt();
		
		int days = switch (month) {
		case 1, 3, 5, 7, 8, 10, 12 -> {
			yield 31;
		}
		case 4, 6, 9, 11 -> {
			yield 30;
		}
		case 2 -> {
			yield 28;
		}
		default -> {
			yield 0;
		}
		};
		
		System.out.println(month + "월은 " + days + "일 입니다.");
	}

}
