package org.example;

import io.vavr.Function1;
import io.vavr.Function3;

public class Curring {
    public static void main(String[] args) {
        Function3<Integer, Integer, Integer, Integer> sum = (a, b, c) -> a + b + c;
        Function1<Integer, Function1<Integer, Integer>> add2 = sum.curried().apply(2);
        Function1<Integer, Integer> add2And3 = add2.curried().apply(3);
        System.out.println(add2And3.apply(4));
    }
}
