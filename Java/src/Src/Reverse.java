package Src;

public class Reverse {
    public static int reverse(int x) {
        int array[] = new int[10];
        for(int index = 0; index < 10; index++) {
        	array[index] = 0;
        }
        
        for (int i = 9; i >= 0; i--){
        	int divisible = x / pow(10, i);
            array[i] = divisible;
            x -= divisible * pow(10, i);
        }
        boolean start = false;
        int answer = 0;
        int power = 0;
        for (int i = 9; i >= 0; i--){
        	if (array[i] != 0) {
        		start = true;
        	}
        	if(start) {
        		try {
        			answer = Math.addExact(answer, Math.multiplyExact(pow(10, power) , array[i]));
        			power += 1;
        		} catch(ArithmeticException e) {
        			return 0;
        		}
        		
        		
        	}
        }
            
        
        return answer;
    }
    
    public static int pow(int x, int y){
    	if(y == 0) {
    		return 1;
    	}
        int answer = x;
        for (int i = 0; i < y-1; i++){
            answer *= x;
        }
        return answer;
    }
    
    public static void main(String[] args ) {
    	System.out.println(reverse(321));
    }
}

