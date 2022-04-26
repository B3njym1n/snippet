package org.example;

import io.vavr.Function2;
import io.vavr.control.Try;

public class Monads {
    public static void main(String[] args) {
        /*
        Try
        The monad Try includes an execution capturing of a possible exception, its two possible return values are the case of failure by exception or the value if it has gone well.
        Some useful methods of the Try are:
.isSuccess () -> as the name itself indicates, returns a boolean by checking if it is a success.
.isFailure () -> returns a boolean by checking if it is a failure.
        get () -> get the value in case it has gone correctly, if a get is made and it is not checked if it done without checking if it is success, it will drop the exception.
        map () -> map over the value in case it went well, if it is a failure it will not be executed.
                getOrElse (T) -> which allows to return a default value in the case of error.
        getOrElse (Supplier) -> which allows to pass another function in the case of error.
        recover (throwable -> {}) -> Same as getOrElse but in this case we will have the exception that has been thrown to be able to achieve it or to be able to return different values depending on the type of exception.
                */

        Function2<Integer, Integer, Integer> divide = (n1, n2) -> n1 / n2;
        Try.of(() -> divide.apply(10, 0)).isFailure();
        Try.of(() -> divide.apply(10, 5)).isSuccess();
        Try.of(() -> divide.apply(10,3)).get();

    }
}
