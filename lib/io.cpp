#include "io.hpp"

void Data_in::check_space(size_t size) const {
    if ((ptrdiff_t)size > (end - cur)) {
        throw IOError(cur - start);
    }
}

void Data_in::raw(void* data, size_t size) {
    check_space(size);
    std::memcpy(data, cur, size);
    cur += size;
}

void Data_in::point2d(r3dPoint2D& value) { raw(&value, sizeof(value)); }

void Data_in::point3d(r3dPoint3D& value) { raw(&value, sizeof(value)); }

void Data_in::pad(size_t S) {
    check_space(S);
    cur += S;
}

void Data_in::zstr(std::string& value) {
    value.clear();
    while (cur != end) {
        char c = *cur++;
        if (c == '\0') {
            break;
        }
        value.push_back(c);
    }
}

void Data_in::fstr(std::string& value, size_t S) {
    check_space(S);
    value.clear();
    value.resize(S);
    std::memcpy(value.data(), cur, S);
    cur += S;
    auto const zero = value.find('\0');
    if (zero != std::string::npos) {
        value.resize((size_t)zero);
    }
}

void Data_in::sstr(std::string& value) {
    uint32_t size = {};
    num<uint32_t>(size);
    value.clear();
    value.resize(size);
    raw(value.data(), size);
    cur += size;
    auto const zero = value.find('\0');
    if (zero != std::string::npos) {
        value.resize((size_t)zero);
    }
}

void Data_in::szstr(std::string& value) { sstr(value); }

void Data_out::raw(void const* data, size_t size) {
    buffer.insert(buffer.end(), (char const*)data, (char const*)data + size);
}

void Data_out::pad(size_t size) { buffer.insert(buffer.end(), size, '\0'); }

void Data_out::zstr(std::string const& value) { raw(value.data(), value.size() + 1); }

void Data_out::point2d(const r3dPoint2D& value) { raw(&value, sizeof(value)); }

void Data_out::point3d(const r3dPoint3D& value) { raw(&value, sizeof(value)); }

void Data_out::fstr(std::string const& value, size_t S) {
    size_t const cur = buffer.size();
    size_t const size = value.size();
    if ((size + 1) > S) {
        throw IOError(cur);
    }
    buffer.resize(cur + S);
    std::memcpy(buffer.data() + cur, value.data(), size);
    std::memset(buffer.data() + cur + size, 0, S - size);
}

void Data_out::sstr(std::string const& value) {
    uint32_t const size = static_cast<uint32_t>(value.size());
    num<uint32_t>(size);
    raw(value.data(), size);
}

void Data_out::szstr(std::string const& value) {
    uint32_t const size = static_cast<uint32_t>(value.size() + 1);
    num<uint32_t>(size);
    raw(value.data(), size);
}
