# Решение

В этой директории лежат зашифрованные файлы с решением.
Для расшифровки выполните:

```sh
openssl enc -d -aes-256-cbc -pbkdf2 -in real48.cpp.enc -out real48.cpp
openssl enc -d -aes-256-cbc -pbkdf2 -in real48.hpp.enc -out real48.hpp
```

После этого в директории появятся файлы `real48.cpp` и `real48.hpp`.
Для выведения ключа шифрования понадобится пароль.
