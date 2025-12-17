# 1. 定义目标路径（示例：D:\test_folder）
$targetPath = ".\\"

# 2. 预览要删除的exe文件（确认列表）
Write-Host "即将删除的exe文件："
Get-ChildItem -Path "$targetPath\*.exe" -Recurse

# 3. 确认后执行删除（按回车继续，按Ctrl+C取消）
Read-Host -Prompt "确认删除以上文件？按Enter继续，按Ctrl+C取消"

# 4. 执行删除
Remove-Item -Path "$targetPath\*.exe" -Recurse -Force -ErrorAction SilentlyContinue
Write-Host "删除完成！"