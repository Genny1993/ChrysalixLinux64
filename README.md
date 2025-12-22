# Chrysalix

Chrysalix is an interpreted programming language with low-level syntax and high-level capabilities.  
It is minimalist, explicit, strict, and bare — every instruction performs one clear action, without syntactic sugar or hidden behavior.  

---

## 💡 Features

- 🧱 Simple syntax: `instruction param1, param2, ...`
- 📦 Built-in array and dictionary support
- 🧭 Recursive search (`rin`, `rinall`) and intersection (`intersect`)
- 🔄 Dynamic memory, typing, arithmetic, string ops
- 🌍 Multi-language interpreter output (Russian, English)

---
## 📦 Install

```
git clone https://github.com/Genny1993/ChrysalixLinux64.git
cd ChrysalixLinux64/build
cmake ..
make
./chrysalix
```

---
## 🚀 Example code

```plaintext
> 5
var $b, 3
>calc '+', $b
>print '\n'
