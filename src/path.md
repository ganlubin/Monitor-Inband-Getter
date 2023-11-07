

  g++ -o main main.cpp tools.cpp jsonPackage.cpp Procps.cpp Boost_process.cpp -lprocps


  我的项目目录如下：
```markdown
- Monitor-Inband-Getter
  - src
    - .vscode
      - settings.json
    - Boost_process_info_process.txt
    - Boost_process_info_system.txt
    - Boost_process.cpp
    - Boost_process.hpp
    - json.hpp
    - jsonPackage.cpp
    - jsonPackage.hpp
    - main
    - main.cpp
    - output.txt
    - path.md
    - Procps
    - Procps.cpp
    - Procps.hpp
    - Procps.txt
    - resoures.json
    - test
    - test.cpp
    - tools
    - tools.cpp
    - tools.hpp
    - TopExplaination.txt
    - Meminfo_Getter.hpp
    - Meminfo_Getter.cpp
  - README.md
```
编译命令是：
```bash
g++ -o main main.cpp tools.cpp jsonPackage.cpp Procps.cpp Boost_process.cpp -lprocps
```
请为我编写Cmake文件，要求是在src目录下的build目录中编译、创建可执行文件，在编译上尽可能严格，使用C++17编译，开启编译优化