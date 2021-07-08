#!/usr/bin/env sh

# 终止一个错误
set -e

# 构建
npm run docs:build

# 进入生成的构建文件夹
cd docs/.vuepress/dist

# 如果你是要部署到自定义域名
# echo 'www.example.com' > CNAME
echo `pwd`
git init
git add -A
git commit -m 'deploy'

# 如果你想要部署到 https://<USERNAME>.github.io
# git push -f git@github.com:<USERNAME>/<USERNAME>.github.io.git master

# 如果你想要部署到 https://<USERNAME>.github.io/<REPO>
git push -f git@github.com:alonglyn/alonglyn.github.io.git master:gh-pages

cd -