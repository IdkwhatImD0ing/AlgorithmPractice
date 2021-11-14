package Src;

public class Roman {
	public static void main(String[] args ) {
    	System.out.println(romanToInt("MCMXCIV"));
    }
	
	public static int romanToInt(String s) {
		int length = s.length();
		boolean subtraction = false;
		int result = 0;
		for (int i = 0; i < length; i++) {
			if(s.charAt(i) == 'I') {
				result++;
			}
			else if(s.charAt(i) == 'V') {
				if(i != 0 && s.charAt(i-1) == 'I') {
					result += 4;
					result -= 1;
				}
				else {
					result += 5;
				}
			}
			else if(s.charAt(i) == 'X') {
				if(i != 0 && s.charAt(i-1) == 'I') {
					result += 9;
					result -= 1;
				}
				else {
					result += 10;
				}
			}
			else if(s.charAt(i) == 'L') {
				if(i != 0 && s.charAt(i-1) == 'X') {
					result += 40;
					result -= 10;
				}
				else {
					result += 50;
				}
			}
			else if(s.charAt(i) == 'C') {
				if(i != 0 && s.charAt(i-1) == 'X') {
					result += 90;
					result -= 10;
				}
				else {
					result += 100;
				}
			}
			else if(s.charAt(i) == 'D') {
				if(i != 0 && s.charAt(i-1) == 'C') {
					result += 400;
					result -= 100;
				}
				else {
					result += 500;
				}
			}
			else if(s.charAt(i) == 'M') {
				if(i != 0 && s.charAt(i-1) == 'C') {
					result += 900;
					result -= 100;
				}
				else {
					result += 1000;
				}
				
			}
		}
		
		return result;
		
	}
}
