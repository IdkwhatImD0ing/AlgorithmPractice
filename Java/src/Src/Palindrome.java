package Src;

import java.util.Stack;

public class Palindrome {
	public static void main(String[] args ) {
    	System.out.println(isPalindrome(121));
    }
	
	public static boolean isPalindrome(int x) {
        if(x < 0){
            return false;
        }
        String newInteger;
        newInteger = String.valueOf(x);
        int length = newInteger.length();
        boolean oddLength = false;
        if(length%2 != 0){
            oddLength = true;
        }
        Stack<Character> contents = new Stack<Character>();
        int half;
        if(oddLength){
            half = (length-1)/2;
        }
        else{
            half = length/2;
        }
        
        for(int i = 0; i < half; i++){
            contents.push((Character)newInteger.charAt(i));
        }
        int originalHalf = half;
        if(oddLength){
            half++;
        }
        for(int i = 0; i < originalHalf; i++){
            if((char)contents.pop() != newInteger.charAt(i+half)){
                return false;
            }
        }
        return true;
    }
}
