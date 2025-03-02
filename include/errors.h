#pragma once

enum class ErrorKind {
    OutOfBounds,
    SpriteAlreadyExists,
};

struct Error {
    ErrorKind kind;
    std::string diagnosis;

    Error(ErrorKind kind, std::string diagnosis): kind(kind), diagnosis(diagnosis) {}
};
