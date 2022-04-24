package org.example;

public class FirstClassFunction {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 5};
        SquareMaker squareMaker = item -> item * item;
        for(int i = 0; i < array.length; i++){
            System.out.println(squareMaker.square(array[i]));
        }
        Offset offset = (v, o) -> v + o;

        for(int i = 0; i < array.length; i++){
            System.out.println(offset.offset(array[i], 3));
        }
    }
}

interface SquareMaker {
    int square(int item);
}

interface Offset {
    int offset(int v, int offset);
}