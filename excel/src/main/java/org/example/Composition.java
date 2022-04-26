package org.example;

import io.vavr.Function1;
import io.vavr.Function3;

import java.util.function.BiFunction;
import java.util.function.Function;

public class Composition {
    public static void main(String[] args) {
        // java8
        Function<Integer, Integer> pow = n -> n * n;
        BiFunction<Integer, Integer, Integer> multiply = (a, b) -> a * b;
        // vavr
        Function1<Integer, Integer> pow1 = (n) -> n * n;
        Function3<Integer, Integer, Integer, Integer> multiply1 = (n1, n2, n3) -> n1 * n2 * n3;
        Function1<String, String> toUpper = String::toUpperCase;
        Function1<String, String> trim = String::trim;
        Function1<String, String> cheers = (s) -> String.format("Hello %s", s);
        System.out.println(trim
                .andThen(toUpper)
                .andThen(cheers)
                .apply("   john"));
        Function1<String, String> composedCheer =
                cheers.compose(trim).compose(toUpper);
        System.out.println(composedCheer.apply(" steve "));
    }
}
