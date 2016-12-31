
try {
    # delete output files
    $currentDir = $PSScriptRoot
    # $currentDir = 'c:\Users\david.zavada\Documents\GitHub\FastSearch\FunctionalTest'
	Write-Host "START TEST from '$currentDir'" -foregroundColor White
    del "$currentDir\*.out"
    
    #path to the fast search
    $fastSearch = "$currentDir\..\Release\FastSearch.exe"

    # get test files
    $testFiles = Get-ChildItem $currentDir -Include *.txt -recurse
    foreach ($file in $testFiles) 
    {
		try {
			$fileName = [System.IO.Path]::GetFileNameWithoutExtension($file.name)
			$patternFilePath = Join-Path $currentDir $("$fileName.pattern")
			$stdoutFilePath = Join-Path $currentDir $("$fileName.out")
			$resultFilePath = Join-Path $currentDir $("$fileName.result")
			$pattern = [IO.File]::ReadAllText($patternFilePath)
			Start-Process $fastSearch -ArgumentList "$file $pattern" -RedirectStandardOutput $stdoutFilePath -Wait
			# compare expected result and output
			$stdoutContent = [IO.File]::ReadAllText($stdoutFilePath)
			$resultContent = [IO.File]::ReadAllText($resultFilePath)
			# if ((!$stdoutContent -and !$resultContent) -or ($stdoutContent -and $resultContent -and (Compare-Object -ReferenceObject $resultContent -DifferenceObject $stdoutContent -caseSensitive))) {
			if ($stdoutContent -eq $resultContent) {
				Write-Host "PASS: $filename" -ForegroundColor Green
			} else {
			   Write-Host "FAILED: $filename" -ForegroundColor Red
			}
		} catch {
			Write-Host "FAILED: $filename" -ForegroundColor Red
			Write-Host $_.Exception.Message -ForegroundColor Yellow
		}
    }
}
catch {
   Write-Host $_.Exception.Message
}
