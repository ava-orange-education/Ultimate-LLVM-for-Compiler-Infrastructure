@g_context = dso_local global i32 5, align 4

define dso_local noundef i32 @checkContext(i32 noundef %userInput) {
entry:
  %userInput.addr = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 %userInput, ptr %userInput.addr, align 4
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr %userInput.addr, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %for.body, label %for.end

for.body:
  %2 = load i32, ptr @g_context, align 4
  %3 = load i32, ptr %userInput.addr, align 4
  %cmp1 = icmp eq i32 %2, %3
  br i1 %cmp1, label %if.then, label %if.end

if.then:
  %4 = load i32, ptr @g_context, align 4
  %add = add nsw i32 %4, 1
  store i32 %add, ptr @g_context, align 4
  br label %if.end

if.end:
  br label %for.inc

for.inc:
  %5 = load i32, ptr %i, align 4
  %inc = add nsw i32 %5, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond

for.end:
  call void @llvm.trap()
  unreachable
}

declare void @llvm.trap() #1

define dso_local noundef i32 @main(i32 noundef %argc, ptr noundef %argv) {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca ptr, align 8
  store i32 0, ptr %retval, align 4
  store i32 %argc, ptr %argc.addr, align 4
  store ptr %argv, ptr %argv.addr, align 8
  %call = call noundef i32 @checkContext(i32 noundef 10)
  ret i32 0
}
