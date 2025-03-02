/*
 * Similar to the <expected> system header, the Result class assimilates the
 * Result enum API from Rust.
 *
 * This header can come in handy when working with a compiler that doesn't support
 * C++23, since <expected> is only available in C++32 and onward.
*/
#pragma once

#include <variant>
#include <stdexcept>

// Assimilates Rust's `Result` API, which contains the success case
// and stores the error case within a value instead of playing throw and catch
template <typename V, typename E>
class Result {
    std::variant<V, E> m_result;

public:
    Result(const V& val) : m_result(val) {}  // Success case
    Result(const E& err) : m_result(err) {} // Error case

    // checks if the value is the success case
    bool isOk() const {
        return std::holds_alternative<V>(this->m_result);
    }

    // checks if the value is the error case
    bool isErr() const {
        return std::holds_alternative<E>(this->m_result);
    }

    // returns success case's value
    V unwrap() const {
        if (this->isOk()) {
            return std::get<V>(this->m_result);
        }
        throw std::runtime_error("Error: Unwrapping a failed result!");
        exit(1);
    }

    // returns the error value
    E unwrapErr() const {
        if (this->isErr()) {
            return std::get<E>(this->m_result);
        }
        throw std::runtime_error("Error: Unwrapping a successful result!");
        exit(1); // Exit the program on error
    }
};
