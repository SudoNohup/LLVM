; ModuleID = 'inputfile/jianyu-opt.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: nounwind
define void @test(i32 %x) #0 {
entry:
  ret void
}

; Function Attrs: nounwind
define i32 @sum(i32 %a, i32 %b, i32 %c) #0 {
entry:
  %cmp = icmp sgt i32 %c, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %d.0 = phi i32 [ %a, %if.then ], [ %b, %if.else ]
  %add = add nsw i32 %a, 1
  %add1 = add nsw i32 %d.0, %add
  ret i32 %add1
}

; Function Attrs: nounwind
define void @test02(i32 %a, i32 %b) #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ]
  %cmp = icmp slt i32 %i.0, %b
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i.0, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

; Function Attrs: nounwind
define void @test021(i32 %a, i32 %b) #0 {
entry:
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  br label %do.cond

do.cond:                                          ; preds = %do.body
  %cmp = icmp sgt i32 %b, 0
  br i1 %cmp, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  ret void
}

; Function Attrs: nounwind
define void @test022(i32 %a) #0 {
entry:
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %x.0 = phi i32 [ %a, %entry ], [ %add, %do.cond ]
  %add = add nsw i32 %x.0, 1
  br label %do.cond

do.cond:                                          ; preds = %do.body
  %cmp = icmp slt i32 %add, 10
  br i1 %cmp, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  ret void
}

; Function Attrs: nounwind
define i32 @stdloop123(i32 %a, i32 %b) #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ]
  %x.0 = phi i32 [ -100, %entry ], [ %add, %for.inc ]
  %cmp = icmp slt i32 %i.0, -1
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %add = add nsw i32 %a, %b
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i.0, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret i32 %x.0
}

; Function Attrs: nounwind
define i32 @cond3(i32 %u, i32 %v) #0 {
entry:
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %x.0 = phi i32 [ 1, %entry ], [ 4, %do.cond ]
  %v.addr.0 = phi i32 [ %v, %entry ], [ %dec, %do.cond ]
  %u.addr.0 = phi i32 [ %u, %entry ], [ %u.addr.1, %do.cond ]
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %x.0)
  %cmp = icmp slt i32 %u.addr.0, %v.addr.0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %do.body
  %inc = add nsw i32 %u.addr.0, 1
  br label %if.end

if.end:                                           ; preds = %if.then, %do.body
  %u.addr.1 = phi i32 [ %inc, %if.then ], [ %u.addr.0, %do.body ]
  %dec = add nsw i32 %v.addr.0, -1
  br label %do.cond

do.cond:                                          ; preds = %if.end
  %cmp1 = icmp sge i32 %dec, 9
  br i1 %cmp1, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  ret i32 4
}

declare i32 @printf(i8*, ...) #1

; Function Attrs: nounwind
define i32 @cond1(i32 %u, i32 %v) #0 {
entry:
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %x.0 = phi i32 [ 1, %entry ], [ %x.1, %do.cond ]
  %v.addr.0 = phi i32 [ %v, %entry ], [ %dec, %do.cond ]
  %u.addr.0 = phi i32 [ %u, %entry ], [ %u.addr.1, %do.cond ]
  %cmp = icmp slt i32 %u.addr.0, %v.addr.0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %do.body
  %add = add nsw i32 %u.addr.0, 1
  br label %if.end

if.end:                                           ; preds = %if.then, %do.body
  %x.1 = phi i32 [ 2, %if.then ], [ %x.0, %do.body ]
  %u.addr.1 = phi i32 [ %add, %if.then ], [ %u.addr.0, %do.body ]
  %dec = add nsw i32 %v.addr.0, -1
  br label %do.cond

do.cond:                                          ; preds = %if.end
  %cmp1 = icmp sge i32 %dec, 9
  br i1 %cmp1, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  ret i32 %x.1
}

; Function Attrs: nounwind
define i32 @hc1(i32 %a, i32 %b) #0 {
entry:
  %M = alloca [100 x i32], align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %while.body ]
  %t.0 = phi i32 [ 0, %entry ], [ %mul, %while.body ]
  %cmp = icmp slt i32 %i.0, 20
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %inc = add nsw i32 %i.0, 1
  %mul = mul nsw i32 %a, %b
  %arrayidx = getelementptr inbounds [100 x i32]* %M, i32 0, i32 %inc
  store i32 %mul, i32* %arrayidx, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  ret i32 %t.0
}

; Function Attrs: nounwind
define i32 @hc11(i32 %a, i32 %b) #0 {
entry:
  %M = alloca [100 x i32], align 4
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %do.cond ]
  %inc = add nsw i32 %i.0, 1
  %mul = mul nsw i32 %a, %b
  %arrayidx = getelementptr inbounds [100 x i32]* %M, i32 0, i32 %inc
  store i32 %mul, i32* %arrayidx, align 4
  br label %do.cond

do.cond:                                          ; preds = %do.body
  %cmp = icmp slt i32 %inc, 20
  br i1 %cmp, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  ret i32 %mul
}

; Function Attrs: nounwind
define i32 @stdloop(i32 %x) #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %a.0 = phi i32 [ 100, %entry ], [ %add, %for.inc ]
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ]
  %cmp = icmp slt i32 %i.0, 10
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %add = add nsw i32 %x, 1
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i.0, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret i32 %a.0
}

; Function Attrs: nounwind
define i32 @test024(i32 %a, i32 %b) #0 {
entry:
  br label %do.body

do.body:                                          ; preds = %do.cond2, %entry
  br label %do.body1

do.body1:                                         ; preds = %do.cond, %do.body
  %add = add nsw i32 %a, 1
  br label %do.cond

do.cond:                                          ; preds = %do.body1
  %cmp = icmp sgt i32 %b, 0
  br i1 %cmp, label %do.body1, label %do.end

do.end:                                           ; preds = %do.cond
  br label %do.cond2

do.cond2:                                         ; preds = %do.end
  %sub = sub nsw i32 %b, 1
  %cmp3 = icmp sgt i32 %sub, 0
  br i1 %cmp3, label %do.body, label %do.end4

do.end4:                                          ; preds = %do.cond2
  ret i32 %add
}

; Function Attrs: nounwind
define i32 @stdloop1(i32 %x) #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %a.0 = phi i32 [ undef, %entry ], [ %add, %for.inc ]
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ]
  %cmp = icmp slt i32 %i.0, 10
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %add = add nsw i32 %x, 1
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i.0, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret i32 %a.0
}

; Function Attrs: nounwind
define i32 @cond25(i32 %u, i32 %v) #0 {
entry:
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %v.addr.0 = phi i32 [ %v, %entry ], [ %dec, %do.cond ]
  %u.addr.0 = phi i32 [ %u, %entry ], [ %u.addr.1, %do.cond ]
  %cmp = icmp slt i32 %u.addr.0, %v.addr.0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %do.body
  %inc = add nsw i32 %u.addr.0, 1
  br label %if.end

if.end:                                           ; preds = %if.then, %do.body
  %x.0 = phi i32 [ 2, %if.then ], [ 3, %do.body ]
  %u.addr.1 = phi i32 [ %inc, %if.then ], [ %u.addr.0, %do.body ]
  %dec = add nsw i32 %v.addr.0, -1
  br label %do.cond

do.cond:                                          ; preds = %if.end
  %cmp1 = icmp sge i32 %dec, 9
  br i1 %cmp1, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  ret i32 %x.0
}

; Function Attrs: nounwind
define void @test028(i32 %a, i32 %b) #0 {
entry:
  br label %do.body

do.body:                                          ; preds = %do.cond2, %entry
  br label %do.body1

do.body1:                                         ; preds = %do.cond, %do.body
  br label %do.cond

do.cond:                                          ; preds = %do.body1
  %cmp = icmp sgt i32 %b, 0
  br i1 %cmp, label %do.body1, label %do.end

do.end:                                           ; preds = %do.cond
  br label %do.cond2

do.cond2:                                         ; preds = %do.end
  %sub = sub nsw i32 %b, 1
  %cmp3 = icmp sgt i32 %sub, 0
  br i1 %cmp3, label %do.body, label %do.end4

do.end4:                                          ; preds = %do.cond2
  ret void
}

; Function Attrs: nounwind
define i32 @stdloop0(i32 %x, i32 %y) #0 {
entry:
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %add = add nsw i32 %x, 1
  br label %do.cond

do.cond:                                          ; preds = %do.body
  %cmp = icmp sgt i32 %y, 0
  br i1 %cmp, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  ret i32 %add
}

; Function Attrs: nounwind
define i32 @hc16(i32 %a, i32 %b) #0 {
entry:
  %M = alloca [100 x i32], align 4
  %arrayidx = getelementptr inbounds [100 x i32]* %M, i32 0, i32 0
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %p.0 = phi i32* [ %arrayidx, %entry ], [ %incdec.ptr, %do.cond ]
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %do.cond ]
  %inc = add nsw i32 %i.0, 1
  %mul = mul nsw i32 %a, %b
  %arrayidx1 = getelementptr inbounds i32* %p.0, i32 %inc
  store i32 %mul, i32* %arrayidx1, align 4
  %incdec.ptr = getelementptr inbounds i32* %p.0, i32 1
  %arrayidx2 = getelementptr inbounds i32* %incdec.ptr, i32 0
  store i32 0, i32* %arrayidx2, align 4
  br label %do.cond

do.cond:                                          ; preds = %do.body
  %cmp = icmp slt i32 %inc, 20
  br i1 %cmp, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  ret i32 0
}

; Function Attrs: nounwind
define i32 @hc161(i32 %a, i32 %b) #0 {
entry:
  %M = alloca [100 x i32], align 4
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %do.cond ]
  %inc = add nsw i32 %i.0, 1
  %mul = mul nsw i32 %a, %b
  %arrayidx = getelementptr inbounds [100 x i32]* %M, i32 0, i32 %inc
  store i32 %mul, i32* %arrayidx, align 4
  %arrayidx1 = getelementptr inbounds [100 x i32]* %M, i32 0, i32 0
  store i32 0, i32* %arrayidx1, align 4
  br label %do.cond

do.cond:                                          ; preds = %do.body
  %cmp = icmp slt i32 %inc, 20
  br i1 %cmp, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  ret i32 0
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
