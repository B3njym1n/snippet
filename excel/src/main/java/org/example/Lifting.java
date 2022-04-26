package org.example;

import io.vavr.Function1;
import io.vavr.control.Option;

public class Lifting {
    public static void main(String[] args) {
        /*
        With lifting what we get is to deal with the exceptions when composing the functions, with which the function will return an Option.none in case that an exception and Option.some, in case everything has gone correctly.
        This is very useful when composing functions that use third-party libraries that can return exceptions.
        */
        Function1<String, String> toUpper = (s) -> {
            if (s.isEmpty()) throw new IllegalArgumentException("input can not be null");
            return s.toUpperCase();
        };
        Function1<String, String> trim = String::trim;
        Function1<String, String> cheers = (s) -> String.format("Hello %s", s);
        Function1<String, String> composedCheer = cheers.compose(trim).compose(toUpper);

        Function1<String, Option<String>> lifted = Function1.lift(composedCheer);

        System.out.println(lifted.apply(""));
    }
}
