package Src;

public class PassByReferenceOrValue {
	
	public static class Dog{
		private String name;
		public Dog(String input) {
			name = input;
		}
		
		public void setName(String input) {
			name = input;
		}
		
		public String getName() {
			return name;
		}
	}
	
	public static void main(String[] args) {
		Dog newDog = new Dog("Gold");
		System.out.println(newDog.getName());
		System.out.println(changeName(newDog, "Silver").getName());
		System.out.println(newDog.getName());
		Dog newDog2 = changeName(newDog, "Silver");
		newDog = newDog2;
		System.out.println(newDog.getName());
		newDog2.setName("Gold");
		System.out.println(newDog.getName());
		

		
	}
	
	public static Dog changeName(Dog inputDog, String input) {
		inputDog.setName("Bronze");
		inputDog = new Dog(input);
		inputDog.setName("Plat");
		return(inputDog);
	}
}
