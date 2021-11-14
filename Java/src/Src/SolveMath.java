package Src;

public class SolveMath {
	public static void main(String[] args) {
		System.out.println("Test");
		double solution;
		double bot;
		double top;

		for(double x = 0.01; x < 20; x = x + 0.01) {
			for(double y = 0.01; y < 20; y = y + 0.01) {
				System.out.println(x);
				System.out.println(y);
				top = 3 * Math.pow(x, 2);
				bot = 22 * x - 3 * Math.pow(y, 2);
				solution = (double)top/bot;
				if(solution == 0) {
					System.out.println("SolutionFound");
					System.out.println(x);
					System.out.println(y);
					return;	
				}
				if(x == 10 && y == 10) {
					System.out.println("Reached midpoint");
				}
				
			}
		}
	}
}
