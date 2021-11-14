package Src;

import java.util.Stack;

public class Parenthesis {
	public static boolean isValid(String s) {
        int length = s.length();
        if(length%2 != 0){
            return false;
        }
        Stack<Character> contents = new Stack<Character>();
        
       
        for (int i = 0; i < length; i++) {
        	if(s.charAt(i) == '(') {
        		contents.push((Character)s.charAt(i));
        	}
        	else if(s.charAt(i) == '{') {
        		contents.push((Character)s.charAt(i));
        	}
        	else if(s.charAt(i) == '[') {
        		contents.push((Character)s.charAt(i));
        	}
        	else if(contents.isEmpty()) {
        		return false;
        	}
        	else if(s.charAt(i) == ')') {
        		if((char)contents.pop() != '(') {
        			return false;
        		}
        	}
        	else if(s.charAt(i) == '}') {
        		if((char)contents.pop() != '{') {
        			return false;
        		}
        	}
        	else if(s.charAt(i) == ']') {
        		if((char)contents.pop() != '[') {
        			return false;
        		}
        	}
        }
        if(!contents.empty()) {
        	return false;
        }
        return true;
    }
	
	public static void main(String[] args ) {
    	System.out.println(isValid("{[]}"));
    }
}
